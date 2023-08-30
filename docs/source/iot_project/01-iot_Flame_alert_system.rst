.. _iot_Flame:

Blynkを使用した炎警報システム
=============================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/01-iot_Flame_alert_system.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>

この章では、Blynkを使用して自宅の炎警報システムのデモを作成するプロセスをご紹介します。炎センサーを活用することで、自宅での火災の可能性を検出できます。検出した値をBlynkに送ることで、インターネット経由で自宅をリモートで監視できます。火災が発生した場合、Blynkは速やかにメールでお知らせします。

1. 回路の組み立て
--------------------------

.. note::

    ESP8266モジュールは、安定した動作環境を確保するために高い電流が必要です。9Vのバッテリーが接続されていることを確認してください。

.. image:: img/01-Wiring_flame_alert_system.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_flame`
* :ref:`cpn_esp8266`

2. Blynkの設定
-----------------------------

**2.1 テンプレートの作成**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

まず、Blynk上で「Flame Alert System」のテンプレートを作成します。以下の手順に従ってください。

.. image:: img/new/01-create_template_1_shadow.png
    :width: 70%
    :align: center

**HARDWARE** は **ESP8266**、**CONNECT TYPE** は **WiFi** に設定してください。

.. image:: img/new/01-create_template_2_shadow.png
    :width: 70%
    :align: center

.. raw:: html
    
    <br/>  

**2.2 データストリーム**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Datastream** ページで、炎センサーモジュールの値を取得するための **Virtual Pin** 型の **Datastream** を作成します。

.. image:: img/new/01-datastream_1_shadow.png
    :width: 90%
    :align: center

**Virtual Pin** の名前を ``flame_sensor_value`` に設定します。**DATA TYPE** を **Integer** にし、MINとMAXは **0** と **1** に設定します。

.. image:: img/new/01-datastream_2_shadow.png
    :width: 90%
    :align: center

.. raw:: html
    
    <br/> 

**2.3 イベント**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

次に、炎の検出を記録し、メール通知を送る **event** を作成します。

.. image:: img/new/01-event_1_shadow.png
    :width: 80%
    :align: center

.. note::
    こちらの設定に合わせることをお勧めします。そうしないと、プロジェクトを実行するためのコードを修正する必要が出てくるかもしれません。

**EVENT NAME** を ``flame_detection_alert`` に設定します。同時に、イベントがトリガーされたときに送るメールの内容を **DESCRIPTION** で設定できます。また、イベントのトリガー頻度の制限も設定できます。

.. image:: img/new/01-event_2_shadow.png
    :width: 80%
    :align: center

**Notifications** ページへ移動して、メールの設定を行います。

.. image:: img/new/01-event_3_shadow.png
    :width: 80%
    :align: center

.. raw:: html
    
    <br/> 

**2.4 Webダッシュボード**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Unoボードから送られてくるセンサーデータを表示するためにも、 **Web Dashboard** の設定が必要です。

**Web Dashboard** ページに **Lable widget** をドラッグアンドドロップします。

.. image:: img/new/01-web_dashboard_1_shadow.png
    :width: 100%
    :align: center

**Lable widget** の設定ページで、 **Datastream** を **flame_sensor_value(V0)** に選択します。次に、データの値に応じて **WIDGET BACKGROUND** の色が変わるように設定します。表示される値が1の場合、緑色になります。値が0の場合、赤色になります。

.. image:: img/new/01-web_dashboard_2_shadow.png
    :width: 100%
    :align: center

.. image:: img/new/01-web_dashboard_3_shadow.png
    :width: 100%
    :align: center

.. raw:: html
    
    <br/> 

**2.5 テンプレートの保存**
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

最後に、テンプレートを保存してください。

.. image:: img/new/01-save_template_shadow.png
    :width: 70%
    :align: center

テンプレートを編集する必要がある場合は、右上の編集ボタンをクリックできます。

.. image:: img/new/01-save_template_2_shadow.png
    :width: 70%
    :align: center

.. raw:: html
    
    <br/> 


3. コードを実行する
-----------------------------

#. ``ultimate-sensor-kit\iot_project\wifi\01-Flame_alert_system`` のパス内にある ``01-Flame_alert_system.ino`` ファイルを開くか、このコードを **Arduino IDE** にコピーしてください。

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/85d6f0ed-9bff-4b44-9e3e-9e954b0bbc5a/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. 炎検知アラートテンプレートを使ってBlynkデバイスを作成します。その後、 ``BLYNK_TEMPLATE_ID`` 、 ``BLYNK_TEMPLATE_NAME`` 、そして ``BLYNK_AUTH_TOKEN`` を自分のものに置き換えてください。

   .. code-block:: arduino
    
      #define BLYNK_TEMPLATE_ID "TMPxxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Flame Alert System"
      #define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxx"

   .. image:: img/new/01-create_device_1_shadow.png
    :width: 80%
    :align: center

   .. image:: img/new/01-create_device_2_shadow.png
    :width: 80%
    :align: center

   .. image:: img/new/01-create_device_3_shadow.png
    :width: 80%
    :align: center

   .. image:: img/new/01-create_device_4_shadow.png
    :width: 80%
    :align: center

#. 使用するWiFiの ``ssid`` と ``password`` も設定する必要があります。

   .. code-block:: arduino

    char ssid[] = "your_ssid";
    char pass[] = "your_password";

#. 正しいボードとポートを選択したら、 **書き込み** ボタンをクリックしてください。

#. シリアルモニターを開き（ボーレートを115200に設定）、接続成功のメッセージが表示されるまでお待ちください。

   .. image:: img/new/01-ready_1_shadow.png
    :width: 80%
    :align: center

   .. note::

       「ESP is not responding」というメッセージが出た場合は、以下の手順に従ってください。

       * 9Vの電池が接続されていることを確認してください。
       * RSTピンを1秒間GNDに接続して、ESP8266モジュールをリセットします。その後、抜いてください。
       * R4ボードのリセットボタンを押してください。

       この操作を3〜5回繰り返す必要がある場合もありますので、ご注意ください。

#. これで、Blynkが炎センサーからのデータを表示します。ラベルウィジェットでは、炎センサーによって読み取られた値が表示されます。値が1であれば、ラベルの背景は緑色で、0であれば赤色で表示され、アラートメールがBlynkから送信されます。

   .. image:: img/new/01-ready_2_shadow.png
    :width: 80%
    :align: center

#. もしBlynkをモバイルデバイスで使用したい場合は、   :ref:`blynk_mobile` を参照してください。



4. コードの説明
-----------------------------

1. **ライブラリ初期化**

   開始する前に、Arduino、ESP8266 WiFiモジュール、Blynkアプリ間の通信のための必要なライブラリと設定をセットアップすることが重要です。このコードは、データ伝送の適切なボーレートで、ArduinoとESP8266モジュール間のソフトウェアシリアル接続を設定します。

   .. code-block:: arduino
   
       //Set debug prints on Serial Monitor
       #define BLYNK_PRINT Serial
   
       #include <ESP8266_Lib.h>               // Library for ESP8266
       #include <BlynkSimpleShieldEsp8266.h>  // Library for Blynk
   
       // Software Serial on Uno
       #include <SoftwareSerial.h>
       SoftwareSerial EspSerial(2, 3);  // RX, TX
       #define ESP8266_BAUD 115200      // Set the ESP8266 baud rate
       ESP8266 wifi(&EspSerial);

2. **BlynkとWiFiの設定**

   プロジェクトがBlynkアプリと通信できるようにするためには、Wi-Fiネットワークに接続する必要があります。ここで資格情報を指定します。

   .. code-block:: arduino

      // Template ID, Device Name and Auth Token are provided by the Blynk Cloud
      // See the Device Info tab, or Template settings
      #define BLYNK_TEMPLATE_ID "TMPxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Flame Alert System"
      #define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxxx" 
      
      // Your WiFi credentials.
      // Set password to "" for open networks.
      char ssid[] = "your_ssid";
      char pass[] = "your_password";

3. **センサーピン & タイマー宣言**

   炎のピン番号を定義します。
   Blynkライブラリには組み込みタイマーがあり、タイマーオブジェクトを作成します。詳しくは |link_blynk_timer_intro|

   .. code-block:: arduino

       const int sensorPin = 8;
       BlynkTimer timer;

4. **setup()関数**

   この関数内で、sensorPinのピンモードを設定、シリアル通信を開始、BlynkTimerを設定、Blynkアプリに接続するなどの初期設定が行われます。

   - ``timer.setInterval(1000L, myTimerEvent)`` を使用してsetup()のタイマー間隔を設定します。ここでは、 ``myTimerEvent()`` 関数を **1000ms** ごとに実行するように設定しています。 ``timer.setInterval(1000L, myTimerEvent)`` の第一引数を変更することで、 ``myTimerEvent`` の実行間隔を変更できます。

   .. raw:: html
    
    <br/> 

   .. code-block:: arduino

       void setup() {
         pinMode(sensorPin, INPUT);
         Serial.begin(115200);
         EspSerial.begin(ESP8266_BAUD);
         delay(1000);
         timer.setInterval(1000L, myTimerEvent);
         Blynk.config(wifi,BLYNK_AUTH_TOKEN);
         Blynk.connectWiFi(ssid, pass);
       }

5. **loop()関数**

   メインループはBlynkとタイマーサービスを継続的に実行します。

   .. code-block:: arduino

       void loop() {
         Blynk.run();
         timer.run();
       }

6. **myTimerEvent() & sendData()関数**

   

   .. code-block:: arduino
 
       void myTimerEvent() {
         // Please don't send more that 10 values per second.
         sendData();  // Call function to send sensor data to Blynk app
       }

   ``sendData()`` 関数は炎センサーからの値を読み取り、それをBlynkに送信します。炎を検出すると（値0）、Blynkアプリに ``flame_detection_alert`` イベントを送信します。

   - ``Blynk.virtualWrite(vPin, value)`` を使用して、Blynkの仮想ピンV0にデータを送信します。詳しくは |link_blynk_virtualWrite| 。

   - ``Blynk.logEvent("event_code")`` を使用して、Blynkにイベントをログします。詳しくは |link_blynk_logEvent| 。

   .. raw:: html
    
    <br/> 

   .. code-block:: arduino
       
      void sendData() {
        int data = digitalRead(sensorPin);
        Blynk.virtualWrite(V0, data);  // send data to virtual pin V0 on Blynk
        Serial.print("flame:");
        Serial.println(data);  // Print flame status on Serial Monitor
        if (data == 0) {
          Blynk.logEvent("flame_alert");  // log flame alert event if sensor detects flame
        }
      }

**参考**

- |link_blynk_doc|
- |link_blynk_quickstart| 
- |link_blynk_virtualWrite|
- |link_blynk_logEvent|
- |link_blynk_timer_intro|

