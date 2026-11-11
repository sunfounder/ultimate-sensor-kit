.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Bluetooth_oled:

14. Bluetooth OLED
==================

スマートフォンで入力し、128 x 64 の OLED で読みます。LCD のプロジェクトに似ています
が、表示器が小さく、スケッチは文がいつ終わったかを推測する必要があります。スマート
フォンは文字を 1 つずつ送るのであって、まとめて 1 かたまりで送るわけではありませ
ん。


1. 回路を組み立てる
-----------------------------

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。


.. image:: ../img/12-Wiring_oled.png
   :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_olde`


2. コードを書き込む
-----------------------------

#. ``14-Bluetooth_oled.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\14-Bluetooth_oled`` から開きます。

   .. note::

      ライブラリマネージャーから **Adafruit SSD1306** と **Adafruit GFX Library** を
      インストールしてください。

#. **Arduino UNO R4 Minima** と正しいポートを選び、**Upload** をクリックします。

#. シリアルモニターを **115200** で開きます。送ったテキストはそこにも表示されます。


3. スマートフォンからテキストを送る
-----------------------------------

#. LightBlue を開き **Scan** をタップして **SunFounder-C2** に接続し、サービス
   **0xA002**、Characteristic **C304** の順に開きます。

#. **Write new value** をタップし、右上の形式を **UTF-8 String** にして ``Hello`` を
   入力します。図は送信直前の入力欄です。

   .. image:: ../img/ble_lightblue_hello.png
      :width: 80%

#. 送信すると OLED とシリアルモニターに単語が表示されます。

#. 別の単語を送ると前のものが置き換わります。表示はスクロールしません。

   .. note::

      メッセージが完了したかを決める規則は 2 つあります。``#`` で終えるか、単に入力を
      やめるかです。スケッチは **120ms** の無音を待ち、その時点であるものを 1 つの
      メッセージとして扱います。

      表示器は 21 文字 4 行です。それより長いテキストは切り詰められます。


4. コードの説明
-----------------------------

#. **表示器**

   .. code-block:: arduino

      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print(message);
      display.display();

   ``0x3C`` はモジュールの I2C アドレスです。``display.display()`` を呼ぶまで画面には
   出ません - スケッチはいったんバッファに書き、それをまとめて画面に送ります。

#. **テキストが終わったことをどう判断するか**

   .. code-block:: arduino

      if (c == '#' || c == '\r' || c == '\n') {
        showMessage();
        continue;
      }
      message += c;
      lastByte = millis();

   ``#`` が来たらすぐにメッセージを終えます。改行も同じです。アプリが自動で改行を付
   けることがあるからです。

#. **120ms の規則**

   .. code-block:: arduino

      if (message.length() > 0 && millis() - lastByte > 120) {
        showMessage();
      }

   BLE は 1 回の書き込みの文字をほぼ間隔なくまとめて送ります。そのかたまりが終わる
   と 120ms が過ぎ、スケッチは持っているものを表示します。おかげで、何も押さなくても
   スマートフォンでの入力が自然に感じられます。

#. **表示したら空にする**

   .. code-block:: arduino

      message = "";

   これがないと次の単語が前のものに連結され、表示がどんどん長くなって切り詰められま
   す。
