.. _iot_Bluetooth_lock_controller:

Bluetooth 錠前コントローラー
=============================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/08-iot_Bluetooth_lock_controller.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>

このプロジェクトは、MIT App Inventorで作成されたAndroidアプリを用いて、Bluetooth経由でサーボモーターをリモート制御し、錠前のメカニズムを模倣します。ユーザーは、アプリを通じて特定のメッセージを送ることで、サーボを「ロック」または「アンロック」の位置に動かせます。

システムは、JDY-31 Bluetoothモジュールを使用してこれらのメッセージを受信し、Arduino Unoボードがそれに応じてサーボモーターの角度を調整します。'1' メッセージを受信するとサーボが「ロック」位置に、'0' メッセージを受信すると「アンロック」位置に移動します。

このAndroidアプリケーションは、|link_appinventor| と呼ばれる無料のウェブベースのプラットフォームを用いて構築されます。このプロジェクトは、スマートフォンとArduinoの連携についての知識を深める絶好の機会です。


1. 回路を組む
-----------------------------

.. image:: img/08-Wiring_Bluetooth_lock_controller.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_servo`


2. Androidアプリを作成
-----------------------------

Androidアプリは、|link_appinventor| という無料のウェブアプリケーションを用いて開発されます。
MIT App Inventorは、直感的なドラッグ&ドロップ機能によってシンプルなアプリケーションを作成できるため、Android開発の入門として理想的です。

それでは、始めましょう。

#. |link_appinventor_login| にアクセスし、「online tool」をクリックしてログインします。MIT App Inventorに登録するにはGoogleアカウントが必要です。

   .. image:: img/new/09-ai_signup_shadow.png
       :width: 90%
       :align: center

#. ログイン後、 **Projects** -> **Import project (.aia) from my computer** に進み、 ``ultimate-sensor-kit\iot_project\bluetooth\03-Bluetooth_lock_controller`` のパスにある ``Bluetooth_controlled_lock.aia`` ファイルをアップロードします。

   直接ダウンロードも可能です: :download:`Bluetooth_controlled_lock.aia</_static/other/Bluetooth_controlled_lock.aia>`

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. ``.aia`` ファイルをアップロードすると、MIT App Inventorソフトウェア上でアプリが表示されます。これは事前に設定されたテンプレートです。次の手順でMIT App Inventorに慣れた後、このテンプレートを修正できます。

#. MIT App Inventorには、主に **Designer** と **Blocks** の2つのセクションがあります。ページの右上隅でこれらのセクションを切り替えることができます。

   .. image:: img/new/09-ai_intro_1_shadow.png

#. **Designer** では、ボタン、テキスト、画面を追加したり、アプリの全体的な見た目を変更できます。

   .. image:: img/new/08-ai_intro_2_shadow.png

#. 次に **Blocks** セクションです。このセクションでは、アプリのGUI上の各コンポーネントをプログラムして、望ましい機能を実現できます。

   .. image:: img/new/08-ai_intro_3_shadow.png

#. スマートフォンにアプリをインストールするには、 **Build** タブに移動します。

   .. image:: img/new/08-ai_intro_4_shadow.png

   * ``.apk`` ファイルを生成できます。このオプションを選ぶと、 ``.apk`` ファイルをダウンロードするか、QRコードをスキャンしてインストールするかを選ぶページが表示されます。インストールガイドに従ってアプリのインストールを完了してください。

     事前にコンパイルされたAPKもこちらからダウンロードできます: :download:`Bluetooth_controlled_lock.apk</_static/other/Bluetooth_controlled_lock.apk>`

   * Google Playや他のアプリマーケットにこのアプリをアップロードする場合は、 ``.aab`` ファイルを生成できます。


3. コードのアップロード
-----------------------------

#. ``ultimate-sensor-kit\iot_project\bluetooth\03-Bluetooth_lock_controller`` のパスにある ``08-Bluetooth_lock_controller.ino`` ファイルを開くか、このコードを **Arduino IDE** にコピーアンドペーストします。

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/b7d14207-953c-479c-89a8-b4a6d8c64e61/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. 対応するボードとポートを選択した後、 **書き込み** ボタンをクリックします。

#. デバッグメッセージを確認するために、シリアルモニターを開いて（ボーレートを **9600** に設定してください）。

4. アプリとBluetoothモジュールの接続
-----------------------------------------------

先に作成したアプリがスマートフォンにインストールされていることを確認してください。

#. 最初に、スマートフォンで **Bluetooth** を有効にします。

   .. image:: img/new/09-app_1_shadow.png
      :width: 60%
      :align: center

#. スマートフォンの **Bluetooth設定** に移動して、 **JDY-31-SPP** のような名前を探します。

   .. image:: img/new/09-app_2_shadow.png
      :width: 60%
      :align: center

#. それをクリックした後、ポップアップウィンドウで **ペアリング** リクエストに同意します。ペアリングコードが求められた場合は、「1234」を入力してください。

   .. image:: img/new/09-app_3_shadow.png
      :width: 60%
      :align: center

#. これで新しくインストールされた **Control_RGB_LED** アプリを開きます。

   .. image:: img/new/08-app_4_shadow.png
      :width: 25%
      :align: center

#. アプリ内で **鍵アイコン** をクリックし、アプリとBluetoothモジュールの接続を確立します。

   .. image:: img/new/08-app_5_shadow.png
      :width: 60%
      :align: center

#. このページでは、ペアリングされているBluetoothデバイスのリストが表示されます。リストから ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` を選択します。各デバイスの名前は、MACアドレスの隣にリストされています。

   .. image:: img/new/08-app_6_shadow.png
      :width: 60%
      :align: center

#. 上のページでデバイスが表示されない場合、このアプリが近くのデバイスをスキャンする権限を持っていない可能性があります。そのような場合は、設定を手動で調整する必要があります。

   * **APP Info** ページにアクセスするには、アプリのアイコンを長押しして選択します。または、このページにアクセスする別の方法があれば、それを使用してください。

   .. image:: img/new/08-app_8_shadow.png
         :width: 60%
         :align: center

   * **権限** ページに移動します。

   .. image:: img/new/08-app_9_shadow.png
         :width: 60%
         :align: center

   * アプリが近くのデバイスをスキャンできるようにするには、 **近くのデバイス** に行って、 **常に** を選択します。

   .. image:: img/new/08-app_10_shadow.png
         :width: 60%
         :align: center

   * それでは、アプリを再起動し、ステップ5と6を繰り返してBluetoothに正常に接続します。

#. 成功した接続の後、メインページにリダイレクトされ、"connected"と表示されます。その後、ロック機構を制御するために「Unlock」または「Lock」をクリックできます。

   .. image:: img/new/08-app_7_shadow.png
      :width: 60%
      :align: center


5. コードの解説
-----------------------------------------------

#. 通信ピンを定義し、SoftwareSerialライブラリを初期化

   .. code-block:: arduino

      const int bluetoothTx = 3;  
      const int bluetoothRx = 4;  
      SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  
   
   上記のコードは、JDY-31 Bluetoothモジュールが通信に使用する送信（Tx）と受信（Rx）ピンを定義します。その後、ArduinoボードとBluetoothモジュールとの通信を可能にするSoftwareSerialライブラリを初期化しています。

#. サーボに関連する定数を定義し、サーボオブジェクトを作成

   .. code-block:: arduino

      const int servoPin = 9;
      const int lockAngle = 180;
      const int unlockAngle = 90;
      Servo myservo;

   この部分では、サーボに接続されたピンと、"ロック"と"アンロック"の位置に対する角度を定義しています。また、サーボモーターを制御するためのServoオブジェクト``myservo``も作成されています。

#. サーボとシリアル通信を初期化

   .. code-block:: arduino

      void setup() {
        myservo.attach(servoPin);
        Serial.begin(9600);
        bleSerial.begin(9600);
      }

#. Bluetoothモジュールの入力に基づいてサーボを制御

   .. code-block:: arduino

      void loop() {
        if (bleSerial.available() > 0) {
          char message = bleSerial.read(); 
          if (message == '1') {  
            myservo.write(lockAngle);
            Serial.println("Locked");
          }
          else if (message == '0') {  
            myservo.write(unlockAngle);
            Serial.println("Unlocked");
          }
        }
      }

   ``loop()`` 関数は繰り返し実行されます。この関数は、Bluetoothモジュールからの入力メッセージを読み取ります。メッセージが'1'であれば、サーボは"ロック"位置に動きます。'0'であれば、"アンロック"位置に動きます。現在の状態（"Locked"または"Unlocked"）は、シリアルモニターに出力されます。
