.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _connect_blynk:

1.4 R4ボードをBlynkに接続する
===============================

#. ESP8266モジュールとR4ボードを再接続します。ここではソフトウェアシリアルが使用されているため、TXとRXはそれぞれR4ボードの2ピンと3ピンに接続されます。

  .. note::
  
       ESP8266モジュールは安定した動作環境を提供するために高電流を必要とします。9Vのバッテリーが接続されていることを確認してください。

  .. image:: img/wiring_r4_quickstart.png

#. ``ultimate-sensor-kit\iot_project\wifi\00-Blynk_quick_start`` パスの下にある ``00-Blynk_quick_start.ino`` ファイルを開くか、このコードを **Arduino IDE** にコピーします。

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/421997b2-aaa7-45d7-926a-f0aec50db99a/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. **Device info** ページからコピーできる以下の三行のコードを置き換えます。これにより、R4ボードがあなたのBlynkアカウントを見つけられるようになります。

   .. code-block:: arduino

       #define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
       #define BLYNK_DEVICE_NAME "Device"
       #define BLYNK_AUTH_TOKEN "YourAuthToken"
   
   .. image:: img/sp20220614174721.png

#. 使用中のWiFiの ``ssid`` と ``password`` を入力します。

   .. code-block:: arduino

       char ssid[] = "ssid";
       char pass[] = "password";

#. コードをR4ボードにアップロードし、シリアルモニターを開いてボーレートを115200に設定します。R4ボードがBlynkと正常に通信すると、シリアルモニターには ``ready`` と表示されます。

   .. image:: img/sp220607_170223.png

   .. note::

       ``ESP is not responding`` というメッセージが表示された場合は、以下の手順に従ってください。

       * 9Vのバッテリーが接続されていることを確認します。
       * RSTピンを1秒間GNDに接続してESP8266モジュールをリセットし、その後、外します。
       * R4ボードのリセットボタンを押します。

       これらの操作を3〜5回繰り返す場合があります。気長に試してください。

#. Blynkのステータスが **offline** から **online** に変わります。

    .. image:: img/sp220607_170326.png
