.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _config_esp8266:

1.1 ESP8266の設定
===============================

このキットに付属しているESP8266モジュールは、すでにATファームウェアが書き込まれていますが、以下の手順に従って設定を変更する必要があります。

1. 回路を作成する。

   .. image:: img/wiring_r4_configure.png
       :width: 800

2. パス ``ultimate-sensor-kit\iot_project\wifi\00-Set_software_serial`` 下の ``00-Set_software_serial.ino`` ファイルを開くか、このコードをArduino IDEにコピーアンドペーストして、コードをアップロードします。

   このコードはArduinoのSoftwareSerialライブラリを用いてソフトウェアシリアル通信を確立し、Arduinoがデジタルピン2と3（RxとTxとして）を介してESP8266モジュールと通信できるようにします。このコードにより、ボーレート115200でArduinoのシリアルモニタを使用して、ESP8266モジュールにATファームウェアコマンドを送信し、その応答を受け取ることができます。

   .. code-block:: Arduino

       #include <SoftwareSerial.h>
       SoftwareSerial espSerial(2, 3); //Rx,Tx

       void setup() {
           // put your setup code here, to run once:
           Serial.begin(115200);
           espSerial.begin(115200);
       }

       void loop() {
           if (espSerial.available()) {
               Serial.write(espSerial.read());
           }
           if (Serial.available()) {
               espSerial.write(Serial.read());
           }
       }


3. 右上隅の虫眼鏡アイコン（シリアルモニタ）をクリックし、ボーレートを **115200** に設定します。（表示される情報があってもなくても問題ありません。次のステップに進んでください。）

   .. image:: img/esp01_configurie_1.png

   .. warning::

        * ``ready`` が表示されない場合は、ESP8266モジュール（RSTをGNDに接続）をリセットして、シリアルモニタを再度開いてください。
        
        * 結果が ``OK`` の場合は、ファームウェアを再書き込む必要があるかもしれません。詳細は :ref:`burn_firmware` を参照してください。それでも解決しない場合は、シリアルモニタのスクリーンショットを sevice@sunfounder.com に送信してください。できるだけ早く問題を解決いたします。

4. **NEWLINE DROPDOWN BOX** をクリックし、ドロップダウンオプションで ``both NL & CR`` を選択し、 ``AT`` を入力します。OKが返ってきたら、ESP8266はR4ボードと正常に接続されたことを意味します。

   .. image:: img/esp01_configurie_2.png

   .. image:: img/esp01_configurie_3.png

5. ``AT+CWMODE=3`` を入力すると、管理モードが **StationとAPの共存** に変更されます。

   .. image:: img/esp01_configurie_4.png

.. 6. ソフトウェアシリアルを後で使用するために、 ``AT+UART=9600,8,1,0,0`` を入力して、ESP8266のボーレートを9600に変更する必要があります。

..    .. image:: img/esp01_configurie_5.png

**参考**

* |link_esp8266_at|
