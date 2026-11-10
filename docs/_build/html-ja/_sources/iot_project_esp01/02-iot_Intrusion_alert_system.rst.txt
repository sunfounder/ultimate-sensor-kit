.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _iot_Intrusion_alert_system:

Blynkを使った侵入警報システム
==================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/02-iot_Intrusion_alert_system.mp4
       "  type="video/mp4">
      ブラウザはビデオタグをサポートしていません。
   </video>

このプロジェクトでは、受動型赤外線（PIR）センサー（HC-SR501）を使用して、簡易な住宅侵入検知システムを実演します。
Blynkアプリでシステムが「外出モード」に設定されている場合、PIRセンサーが動きを監視します。
検出された動きは、Blynkアプリで通知をトリガーし、ユーザーに潜在的な侵入を警告します。

1. 回路の構築
-----------------------------

.. note::

    ESP8266モジュールは、安定した動作環境を提供するために高い電流が必要です。9Vの電池が接続されていることを確認してください。


.. image:: img/02-Wiring_intrusion_alert_system.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_esp8266`
* :ref:`cpn_pir_motion`

2. Blynkの設定
-----------------------------

.. note::
    Blynkに慣れていない場合は、これら2つのチュートリアルを先に読むことを強くお勧めします。 :ref:`iot_blynk_start` は、Blynkの初心者向けガイドで、ESP8266の設定とBlynkへの登録方法が含まれています。 :ref:`iot_Flame` は簡単な例ですが、手順の説明はより詳細です。

**2.1 テンプレートの作成**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

まず、Blynkで **「Intrusion Alert System」** テンプレートを作成する必要があります。

.. image:: img/new/02-create_template_shadow.png
    :width: 80%
    :align: center

**2.2 データストリーム**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

esp8266とuno r4ボードからデータを受け取るために、 **Datastreams** ページで **Virtual Pin** 型の **Datastreams** を作成します。

* 以下の図に従ってVirtual Pin V0を作成します：
   
  **Virtual Pin V0** の名前を **AwayMode** に設定します。 **DATA TYPE** を **Integer** にし、MINとMAXを **0** と **1** に設定します。

  .. image:: img/new/02-datastream_1_shadow.png
      :width: 90%

* 以下の図に従ってVirtual Pin V1を作成します： 

  **Virtual Pin V1** の名前を **Current status** に設定します。 **DATA TYPE** を **String** にします。

  .. image:: img/new/02-datastream_2_shadow.png
      :width: 90%

上記の手順に従って、2つのVirtual Pinを設定したことを確認してください。

.. image:: img/new/02-datastream_3_shadow.png
    :width: 100%

.. raw:: html
    
    <br/> 

**2.3 イベント**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

次に、侵入の検出をログに記録し、メール通知を送る **event** を作成します。

.. note::
    コードの変更が必要になる可能性があるため、私の設定と一致させることをお勧めします。 **EVENT CODE** は ``intrusion_detected`` として設定されていることを確認してください。

.. image:: img/new/02-event_1_shadow.png
    :width: 90%
    :align: center

**Notifications** ページに移動し、メール設定を行います。

.. image:: img/new/02-event_2_shadow.png
    :width: 90%
    :align: center

.. raw:: html
    
    <br/> 

**2.4 Webダッシュボード**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

侵入警報システムと対話するために **Web Dashboard** も設定する必要があります。

**Web Dashboard** ページに **Switch widget** と **Label widget** をドラッグアンドドロップします。

.. image:: img/new/02-web_dashboard_1_shadow.png
    :width: 100%
    :align: center

**Switch widget** の設定ページで、 **Datastream** を **AwayMode(V0)** に選択します。スイッチがオンになったときには「away home」を表示し、オフになったときには「at home」を表示するように、 **ONLABEL** と **OFFLABEL** を設定します。

.. image:: img/new/02-web_dashboard_2_shadow.png
    :width: 100%
    :align: center

**Label widget** の設定ページで、 **Datastream** を **Current status(V1)** に選択します。

.. image:: img/new/02-web_dashboard_3_shadow.png
    :width: 100%
    :align: center

**2.5 テンプレートを保存**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

最後に、テンプレートを保存することを忘れないでください。

.. image:: img/new/02-save_template_shadow.png
    :width: 70%
    :align: center

.. raw:: html
    
    <br/>  

3. コードの実行
-----------------------------

#. ``ultimate-sensor-kit\iot_project\wifi\02-Intrusion_alert_system`` のパスの下で ``02-Intrusion_alert_system.ino`` ファイルを開くか、このコードを **Arduino IDE** にコピーしてください。

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/0f670211-aee7-4bf3-8415-617dc054d514/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. "Intrusion Alert System"のテンプレートを使用して、Blynkデバイスを作成します。その後、 ``BLYNK_TEMPLATE_ID`` 、 ``BLYNK_TEMPLATE_NAME`` 、および ``BLYNK_AUTH_TOKEN`` を自分のものに置き換えてください。

   .. code-block:: arduino
    
      #define BLYNK_TEMPLATE_ID "TMPxxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Intrusion Alert System"
      #define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxx"

#. 使用するWiFiの ``ssid`` と ``password`` も入力する必要があります。

   .. code-block:: arduino

    char ssid[] = "your_ssid";
    char pass[] = "your_password";

#. 適切なボードとポートを選択したら、 **書き込み** ボタンをクリックします。

#. シリアルモニターを開き（ボーレートを115200に設定）、成功した接続などのプロンプトが表示されるまで待ちます。

   .. image:: img/new/02-ready_1_shadow.png
    :width: 80%
    :align: center

   .. note::

       接続時に ``ESP is not responding`` というメッセージが表示された場合は、以下の手順に従ってください。

       * 9Vの電池が接続されていることを確認します。
       * RSTピンを1秒間GNDに接続してESP8266モジュールをリセットし、その後抜きます。
       * R4ボードのリセットボタンを押します。

       時折、上記の操作を3〜5回繰り返す必要がある場合もありますので、ご注意ください。


4. コードの説明
-----------------------------

#. **設定とライブラリ**

   こちらでBlynkの定数と認証情報を設定します。ESP8266 WiFiモジュールとBlynkに必要なライブラリをインクルードしています。

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID "TMPxxxx"
      #define BLYNK_TEMPLATE_NAME "Intrusion Alert System"
      #define BLYNK_AUTH_TOKEN "xxxxxx-"
      #define BLYNK_PRINT Serial

      #include <ESP8266_Lib.h>
      #include <BlynkSimpleShieldEsp8266.h>

#. **Wi-Fiの設定**

   Wi-Fi認証情報を設定し、ESP01モジュールとのソフトウェアシリアル通信を構築します。

   .. code-block:: arduino

      char ssid[] = "your_ssid";
      char pass[] = "your_password";

      SoftwareSerial EspSerial(2, 3);
      #define ESP8266_BAUD 115200
      ESP8266 wifi(&EspSerial);

#. **PIRセンサーの設定**

   PIRセンサーが接続されているピンを定義し、状態変数を初期化します。

   .. code-block:: arduino

      const int sensorPin = 8;
      int state = 0;
      int awayHomeMode = 0;
      BlynkTimer timer;

#. **setup()関数**

   この関数では、PIRセンサーを入力として初期化し、シリアル通信を設定し、Wi-Fiに接続し、Blynkを構成します。

   - ``timer.setInterval(1000L, myTimerEvent)`` を使用して、setup()内でタイマー間隔を設定します。ここでは、 ``myTimerEvent()`` 関数を **1000ms** ごとに実行するように設定しています。

   .. raw:: html
    
    <br/> 

   .. code-block:: arduino

      void setup() {
         pinMode(sensorPin, INPUT);
         Serial.begin(115200);
         EspSerial.begin(ESP8266_BAUD);
         delay(10);
         Blynk.config(wifi, BLYNK_AUTH_TOKEN);
         Blynk.connectWiFi(ssid, pass);
         timer.setInterval(1000L, myTimerEvent);
      }

#. **loop()関数**

   loop関数では、BlynkとBlynkタイマー関数を繰り返し実行します。

   .. code-block:: arduino

      void loop() {
         Blynk.run();
         timer.run();
      }

#. **Blynkアプリとの対話**

   これらの関数は、デバイスがBlynkに接続されたとき、およびBlynkアプリの仮想ピンV0の状態が変わったときに呼び出されます。

   - デバイスがBlynkサーバーに接続するたび、またはネットワークの状態が悪いために再接続するたびに、 ``BLYNK_CONNECTED()`` 関数が呼び出されます。 ``Blynk.syncVirtual()`` コマンドは、単一の仮想ピンの値のリクエストです。指定された仮想ピンは ``BLYNK_WRITE()`` 呼び出しを実行します。詳細は、 |link_blynk_syncing| を参照してください。

   - BLYNKサーバー上の仮想ピンの値が変更されると、 ``BLYNK_WRITE()`` がトリガーされます。詳細は、 |link_blynk_write| にあります。


   .. raw:: html
    
    <br/> 

   .. code-block:: arduino
      
      // This function is called every time the device is connected to the Blynk.Cloud
      BLYNK_CONNECTED() {
         Blynk.syncVirtual(V0);
      }
      
      // This function is called every time the Virtual Pin 0 state changes
      BLYNK_WRITE(V0) {
         awayHomeMode = param.asInt();
         // additional logic
      }

#. **データの処理**

   ``myTimerEvent()`` 関数は毎秒 ``sendData()`` を呼び出します。Blynkで不在モードが有効になっている場合、PIRセンサーを確認して、動きが検出された場合にBlynkに通知を送信します。

   - ``Blynk.virtualWrite(V1, "Somebody in your house! Please check!")`` を使用して、ラベルのテキストを変更します。

   - ``Blynk.logEvent("intrusion_detected");`` を使用して、Blynkにイベントをログします。

   .. raw:: html
    
    <br/> 

   .. code-block:: arduino

      void myTimerEvent() {
         sendData();
      }

      void sendData() {
         if (awayHomeMode == 1) {
            state = digitalRead(sensorPin);  // Read the state of the PIR sensor

            Serial.print("state:");
            Serial.println(state);
        
            // If the sensor detects movement, send an alert to the Blynk app
            if (state == HIGH) {
              Serial.println("Somebody here!");
              Blynk.virtualWrite(V1, "Somebody in your house! Please check!");
              Blynk.logEvent("intrusion_detected");
            }
         }
      }


**参考資料**

- |link_blynk_doc|
- |link_blynk_quickstart| 
- |link_blynk_virtualWrite|
- |link_blynk_logEvent|
- |link_blynk_timer_intro|
- |link_blynk_syncing| 
- |link_blynk_write|
