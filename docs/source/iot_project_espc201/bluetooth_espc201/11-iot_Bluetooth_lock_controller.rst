.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Bluetooth_lock_controller:

11. Bluetooth ロック
=====================

サーボモーターが鍵のボルトの代わりです。スマートフォンから 1 文字送ると回ります。
``1`` で施錠、``0`` で解錠です。

鍵には 2 つの状態しかないので、スケッチに終端記号は要りません。届いた 1 文字がその
まま完全なコマンドになります。


1. 回路を組み立てる
-----------------------------

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。サーボにも専用の電流ピークがあるので、ボード
   の 5V ピンからは給電しないでください。


.. image:: ../img/08-Wiring_Bluetooth_lock_controller.png
   :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_servo`


2. コードを書き込む
-----------------------------

#. ``11-Bluetooth_lock_controller.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\11-Bluetooth_lock_controller`` から開きます。

   .. note::

      スケッチには **Servo** ライブラリが必要です。Arduino IDE に最初から入っている
      ので、通常は何もインストールしません。

#. **Arduino UNO R4 Minima** と正しいポートを選び、**Upload** をクリックします。

#. シリアルモニター（**115200**）に Bluetooth の 2 行が出て、その後は送ったコマンド
   ごとに 1 行ずつ出ます。

   .. code-block:: text

      === ESPC2-01 Bluetooth (BLE) ===
      [OK] BLE is ready - scan for "SunFounder-C2" on your phone
      --------------------------------
      Locked
      Unlocked


3. スマートフォンから施錠・解錠する
-----------------------------------

#. LightBlue を開き **Scan** をタップして **SunFounder-C2** に接続します。

#. サービス **0xA002** を展開し、Characteristic **C304** を開きます。赤い枠が押す
   ボタンです。

   .. image:: ../img/ble_lightblue_write.png
      :width: 80%

#. **Write new value** をタップし、右上の形式を **UTF-8 String** にして ``1`` を入力
   します。図は送信直前の入力欄です。

   .. image:: ../img/ble_lightblue_1.png
      :width: 80%

#. 送信するとサーボが施錠位置へ回り、シリアルモニターに ``Locked`` と出ます。

#. 代わりに ``0`` を入力して送ると、サーボが戻り ``Unlocked`` と出ます。

   .. image:: ../img/ble_lightblue_0.png
      :width: 80%

   .. note::

      角度はスケッチの先頭にある ``lockAngle`` と ``unlockAngle`` です。機構が逆に動
      く場合は、ホーンを手で回すのではなく 2 つの数値を入れ替えてください。元に戻すの
      が簡単です。


4. コードの説明
-----------------------------

#. **サーボ**

   .. code-block:: arduino

      #include <Servo.h>
      Servo myservo;

      const int lockAngle = 0;
      const int unlockAngle = 90;

   ``myservo.write(angle)`` はホーンを 0〜180 度の位置へ動かし、そこに保持します。連
   続回転はしません - 鍵のボルトに必要なのはまさにそれです。

#. **1 文字を待つ**

   .. code-block:: arduino

      if (bleSerial.available() > 0) {
        char message = bleSerial.read();

        if (message == '1') {
          myservo.write(lockAngle);
          Serial.println("Locked");
        } else if (message == '0') {
          myservo.write(unlockAngle);
          Serial.println("Unlocked");
        }
      }

   ``bleSerial.read()`` は **1 文字** を返すので、スマートフォンは ``Lock`` ではなく
   ``1`` を送る必要があります。``1`` でも ``0`` でもないものは、何も言わずに無視され
   ます。

   .. note::

      ``'1'`` のように一重引用符で書くと文字です。``"1"`` の二重引用符だと 1 文字の
      テキストになり、比較がコンパイルできません。

#. **終端記号が要らない理由**

   ここではどのコマンドも 1 文字なので、スケッチの解釈がずれようがありません。ピアノ
   や OLED ではメッセージが長く、そこでは終端記号が必須になります - 次の章の ``*`` と
   ``#`` に注目してください。
