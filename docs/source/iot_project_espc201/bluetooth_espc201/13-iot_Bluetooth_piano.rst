.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_iot_Bluetooth_piano:

13. Bluetooth ピアノ
=====================

ブザーがピアノになります。``NOTE_C4*`` を送ると 0.2 秒だけドの音が鳴ります。

面白いのは末尾のアスタリスクです。これがメッセージの **終わり** を示すので、ス
ケッチは音名が全部そろったことを知ります - そうでなければ ``NOTE_C`` の時点で鳴らそ
うとしてしまいます。


1. 回路を組み立てる
-----------------------------

.. note::

   モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
   の DC ジャックに必ず接続してください。


.. image:: ../img/11-Wiring_Bluetooth_piano.png
   :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_espc201`
* :ref:`cpn_buzzer`


2. コードを書き込む
-----------------------------

#. ``13-Bluetooth_piano.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\bluetooth\13-Bluetooth_piano`` から開きます。

#. **Arduino UNO R4 Minima** と正しいポートを選び、**Upload** をクリックします。

#. シリアルモニターを **115200** で開きます。送った音名がアスタリスクなしで表示され
   ます。

   .. code-block:: text

      NOTE_C4


3. スマートフォンから音を鳴らす
-------------------------------

#. LightBlue を開き **Scan** をタップして **SunFounder-C2** に接続し、サービス
   **0xA002**、Characteristic **C304** の順に開きます。

#. **Write new value** をタップし、右上の形式を **UTF-8 String** にして
   ``NOTE_C4*`` を入力します。図は送信直前の入力欄です。

   .. image:: ../img/ble_lightblue_note.png
      :width: 80%

#. 送信するとブザーが約 0.2 秒ドを鳴らし、シリアルモニターに ``NOTE_C4`` と出ます -
   アスタリスクは使われたあと取り除かれます。

#. 次の 8 音が使えます。

   .. list-table::
      :header-rows: 1
      :widths: 40 60

      * - 送る内容
        - 音
      * - ``NOTE_C4*``、``NOTE_D4*``、``NOTE_E4*``
        - 低いド、レ、ミ
      * - ``NOTE_F4*``、``NOTE_G4*``、``NOTE_A4*``、``NOTE_B4*``
        - ファ、ソ、ラ、シ
      * - ``NOTE_C5*``
        - 1 オクターブ上のド

   .. note::

      **アスタリスクを忘れないでください。** これがないと、スケッチはメッセージの終わ
      りを待ち続け、音は鳴らず、シリアルモニターにも何も出ません。


4. コードの説明
-----------------------------

#. **ブザー**

   .. code-block:: arduino

      tone(buzzerPin, NOTE_C4);
      delay(200);
      noTone(buzzerPin);

   ``tone(pin, frequency)`` はその周波数の矩形波を出し、単純な圧電ブザーが音として鳴
   らします。``NOTE_C4`` はピン番号ではなく、Arduino コアが定義している周波数です。

#. **アスタリスクまで文字を集める**

   .. code-block:: arduino

      while (bleSerial.available() > 0) {
        character = bleSerial.read();
        noteType = noteType + character;

        if (character == '*') {
          noteType = noteType.substring(0, noteType.length() - 1);
          ...
        }
      }

   文字は 1 つずつ集めます。アスタリスクは動作のきっかけであると同時に、取り除くべき
   ものでもあります。``substring(0, length()-1)`` が最後の 1 文字を削り、
   ``NOTE_C4*`` が ``NOTE_C4`` になります。

#. **テキストの比較**

   .. code-block:: arduino

      if (noteType == "NOTE_C4") { tone(buzzerPin, NOTE_C4); }
      else if (noteType == "NOTE_D4") { ... }

   テキストは二重引用符と ``==`` で比較します。``=`` 1 つだと代入になり、コンパイル
   は通りますが永久に動きません。

#. **1 音ごとにリセット**

   .. code-block:: arduino

      noteType = "";
      delay(200);
      noTone(buzzerPin);

   ``noteType`` を空にすることが大切です。これがないと次の音名が前のものに連結され、
   どの比較も一致しなくなります。
