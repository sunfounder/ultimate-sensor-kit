.. _iot_Bluetooth_RGB_controller:

Bluetooth RGB コントローラー
=============================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/09-iot_Bluetooth_RGB_controller.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>

このプロジェクトは、Androidアプリを使用して、スマートフォンを介したBluetooth技術でRGB LEDの色を制御します。

このAndroidアプリケーションは、|link_appinventor| という無料のウェブベースのプラットフォームを活用して構築されます。このプロジェクトは、Arduinoとスマートフォンのインターフェースに慣れる絶好の機会です。

このプロジェクトでは、Arduino Unoに接続されたRGB LEDをJDY-31 Bluetoothモジュール経由で制御します。Androidアプリケーションは、GUI上でのユーザー操作に基づいて、Arduino Unoボードに様々な色の値をBluetooth経由で送信します。Unoボード上のプログラムは、Bluetoothを介したシリアルポートからRGB色値を文字として受け取り、LEDの色をそれに応じて調整します。

1. 回路を作成する
-----------------------------

.. image:: img/09-Wiring_Bluetooth_rgb_controller.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_rgb`


2. Androidアプリを作成する
-----------------------------

Androidアプリケーションは、|link_appinventor| という無料のウェブアプリケーションを使用して開発されます。
MIT App Inventorは、直感的なドラッグアンドドロップ機能を備えているため、Android開発の優れたスタート地点です。

それでは、始めましょう。

#. |link_appinventor_login| にアクセスし、「online tool」をクリックしてログインします。MIT App Inventorで登録するには、Googleアカウントが必要です。

   .. image:: img/new/09-ai_signup_shadow.png
       :width: 90%
       :align: center

#. ログイン後、 **Projects** -> **Import project (.aia) from my computer** に移動します。次に、 ``ultimate-sensor-kit\iot_project\bluetooth\04-Bluetooth_RGB_controller`` のパスにある ``Control_RGB_LED.aia`` ファイルをアップロードします。

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. ``.aia`` ファイルをアップロードした後、MIT App Inventorソフトウェア上でアプリケーションが表示されます。これは事前に設定されたテンプレートです。以下のステップでMIT App Inventorに慣れた後、このテンプレートを変更することができます。

   .. image:: img/new/09-ai_import_2_shadow.png

#. MIT App Inventorには、 **Designer** と **Blocks** という2つの主要なセクションがあります。ページの右上隅でこれら2つのセクションを切り替えることができます。

   .. image:: img/new/09-ai_intro_1_shadow.png

#. **Designer** では、ボタン、テキスト、画面を追加し、アプリケーションの全体的な見た目を変更できます。

   .. image:: img/new/09-ai_intro_2_shadow.png
   
#. 次に、 **Blocks** セクションがあります。このセクションでは、アプリのGUIの各コンポーネントをプログラムして、必要な機能を実装できます。

   .. image:: img/new/09-ai_intro_3_shadow.png

#. スマートフォンにアプリケーションをインストールするには、 **Build** タブに移動します。

   .. image:: img/new/09-ai_intro_4_shadow.png

   * ``.apk`` ファイルを生成できます。このオプションを選択すると、 ``.apk`` ファイルをダウンロードするか、QRコードをスキャンしてインストールするかを選ぶページが表示されます。インストールガイドに従ってアプリケーションのインストールを完了してください。

     こちらからも事前にコンパイルされたAPKをダウンロードできます：:download:`Control_RGB_LED.apk</_static/other/Control_RGB_LED.apk>`


   * Google Playまたは別のアプリマーケットにこのアプリをアップロードしたい場合は、 ``.aab`` ファイルを生成できます。



3. コードのアップロード
-----------------------------

#. ``ultimate-sensor-kit\iot_project\bluetooth\04-Bluetooth_RGB_controller`` のパス下にある ``04-Bluetooth_RGB_controller.ino`` ファイルを開くか、このコードを **Arduino IDE** にコピーします。

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/dc140b60-64ed-4ec0-8e50-53c5340c267e/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. 適切なボードとポートを選択した後、 **書き込み** ボタンをクリックします。

#. シリアルモニターを開き（ボーレートを **9600** に設定）、デバッグメッセージを確認します。

4. アプリとBluetoothモジュールの接続
-----------------------------------------------

既に作成したアプリがスマートフォンにインストールされていることを確認してください。

#. まず、スマートフォンの **Bluetooth** をオンにします。

   .. image:: img/new/09-app_1_shadow.png
      :width: 60%
      :align: center

#. スマートフォンの **Bluetooth設定** に移動し、**JDY-31-SPP** のような名前を探します。

   .. image:: img/new/09-app_2_shadow.png
      :width: 60%
      :align: center

#. クリック後、ポップアップウィンドウで **ペアリング** の要求に同意します。ペアリングコードが求められた場合は「1234」と入力します。

   .. image:: img/new/09-app_3_shadow.png
      :width: 60%
      :align: center

#. 新しくインストールされた **Control_RGB_LED** アプリを開きます。

   .. image:: img/new/09-app_4_shadow.png
      :width: 25%
      :align: center

#. アプリ内で **Connect Bluetooth** をクリックし、アプリとBluetoothモジュールとの接続を確立します。

   .. image:: img/new/09-app_5_shadow.png
      :width: 60%
      :align: center

#. このページには、すべてのペアリング済みBluetoothデバイスが一覧表示されます。リストから ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` オプションを選択します。各デバイスの名前は、そのMACアドレスの隣に表示されます。

   .. image:: img/new/09-app_6_shadow.png
      :width: 60%
      :align: center

#. 上記のページにデバイスが表示されていない場合、このアプリが周辺のデバイスをスキャンする権限がない可能性があります。その場合は、設定を手動で調整する必要があります。

   * **アプリ情報** ページにアクセスするには、アプリアイコンを長押しして選択します。または、このページに到達する他の方法があれば、それを使用してください。

   .. image:: img/new/09-app_8_shadow.png
         :width: 60%
         :align: center

   * **許可** ページに移動します。

   .. image:: img/new/09-app_9_shadow.png
         :width: 60%
         :align: center

   * アプリが周辺のデバイスをスキャンできるようにするには、 **周辺のデバイス** に移動して **常時許可** を選択します。

   .. image:: img/new/09-app_10_shadow.png
         :width: 60%
         :align: center

   * その後、アプリを再起動し、ステップ5と6を繰り返して、Bluetoothに成功裏に接続します。

#. 接続が成功すると、メインページにリダイレクトされ、「connected」と表示されます。ここから、 **Change Color** ボタンをクリックして、RGB値を簡単に変更し、ディスプレイの色を変えることができます。

   .. image:: img/new/09-app_7_shadow.png
      :width: 60%
      :align: center



5. コードの説明
-----------------------------------------------

#. Bluetoothモジュールと変数の初期設定:

   コードは ``SoftwareSerial`` ライブラリをインクルードし、必要な変数を初期設定するところから始まります。

   .. code-block:: arduino

      #include <SoftwareSerial.h>
      SoftwareSerial bleSerial(3, 4);  //Rx,Tx

      #define max_char 12
      char message[max_char];  
      char r_char;             
      byte currentIndex = 0;

      const int redPin = 9;
      const int greenPin = 10;
      const int bluePin = 11;

      int redValue = 0;
      int greenValue = 255;
      int blueValue = 0;

      String redTempValue;
      String greenTempValue;
      String blueTempValue;

      int flag = 0;      
      char currentColor;  

#. setup() 関数について:

   ここでは、RGB LEDの各ピンを出力ピンとして設定し、ArduinoとBluetoothモジュールの両方のシリアル通信をボーレート9600で初期化します。
   
   .. code-block:: arduino

      void setup() {
        pinMode(redPin, OUTPUT);
        pinMode(bluePin, OUTPUT);
        pinMode(greenPin, OUTPUT);
        Serial.begin(9600);
        bleSerial.begin(9600);
      }

#. データの読み取りと処理:

   メインループ内で、Bluetoothモジュールからの着信データを継続的に監視します。データが到着すると、それを解析してRGB値を特定し、RGB LEDの色を適切に設定します。
   
   .. code-block:: arduino

      void loop() {
        while (bleSerial.available() > 0) {
          ... [データの読み取りと処理]
        }

        if (flag == 0) {
          Serial.println(message); 
          analogWrite(redPin, redTempValue.toInt());
          analogWrite(greenPin, greenTempValue.toInt());
          analogWrite(bluePin, blueTempValue.toInt());

          flag = 1;  

          for (int i = 0; i < 12; i++) {
            message[i] = '\0';
          }
          currentIndex = 0;
        }
      }
