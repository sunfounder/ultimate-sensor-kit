.. _iot_Bluetooth_remote_relay:

Bluetooth リモートリレー
=================================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/iot/13-iot_Bluetooth_remote_relay.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>

このプロジェクトでは、MIT App Inventorで作成されたAndroidアプリを用いて、Arduino Unoに接続されたJDY-31 Bluetoothモジュールを介してリレーモジュールをリモート制御します。アプリのボタンが押されると、単純なコマンド（'1'または'0'）がArduinoに送信されます。ArduinoがBluetooth経由でコマンド'1'を受け取ると、リレーが活性化し、'0'を受け取るとリレーが非活性化します。これにより、スマートフォン上でリレーに接続されたデバイスを簡単に制御するインターフェースが提供されます。

Androidアプリは、 |link_appinventor| という無料のWebベースのプラットフォームを用いて構築されます。このプロジェクトは、スマートフォンとArduinoのインターフェースングを理解する絶好の機会となります。


1. 回路を組む
-----------------------------

.. warning ::
    以下の例では、LEDモジュールを制御するためのリレーを使用します。
    **実際のアプリケーションでリレーを他の機器に接続する場合は、高電圧ACに対する細心の注意が必要です。誤用または不正確な使用により、重傷や死に至る可能性があります。そのため、高電圧ACに精通している方のみが対象です。常に安全を最優先してください。**

.. image:: img/13-Wiring_Bluetooth_remote_relay.png
    :width: 75%

* :ref:`cpn_uno`
* :ref:`cpn_jdy31`
* :ref:`cpn_relay`
* :ref:`cpn_rgb`


2. Androidアプリを作成
-----------------------------

Androidアプリは、 |link_appinventor| という無料のWebアプリケーションを使用して開発されます。
MIT App Inventorは、直感的なドラッグアンドドロップ機能を用いて簡単なアプリケーションを作成できるため、Android開発の優れたスタート地点となります。

それでは、始めましょう。

#. |link_appinventor_login| にアクセスし、"online tool"をクリックしてログインします。MIT App Inventorに登録するためにはGoogleアカウントが必要です。

   .. image:: img/new/09-ai_signup_shadow.png
       :width: 90%
       :align: center

#. ログインしたら、 **Projects** -> **Import project (.aia) from my computer** へ進みます。次に、 ``ultimate-sensor-kit\iot_project\bluetooth\08-Bluetooth_remote_relay`` にある ``RemoteRelay.aia`` ファイルをアップロードします。

   または、以下から直接ダウンロードも可能です: :download:`RemoteRelay.aia</_static/other/RemoteRelay.aia>`

   .. image:: img/new/09-ai_import_shadow.png
        :align: center

#. ``.aia`` ファイルをアップロードすると、MIT App Inventorソフトウェア上でアプリケーションが表示されます。これは事前に設定されたテンプレートです。以下のステップでMIT App Inventorに慣れた後、このテンプレートを自由に修正できます。

#. MIT App Inventorには、 **Designer** と **Blocks** という2つの主要なセクションがあります。これらのセクションはページの右上隅で切り替え可能です。

   .. image:: img/new/09-ai_intro_1_shadow.png

#. **Designer** では、ボタンやテキスト、画面の全体的な見た目を調整することができます。

   .. image:: img/new/13-ai_intro_2_shadow.png

#. 次に、 **Blocks** セクションです。このセクションで、アプリのGUIの各コンポーネントをプログラムして、希望する機能を実現できます。

   .. image:: img/new/13-ai_intro_3_shadow.png

#. スマートフォンにアプリケーションをインストールするには、 **Build** タブに進みます。

   .. image:: img/new/08-ai_intro_4_shadow.png

   * ``.apk`` ファイルを生成することができます。このオプションを選ぶと、 ``.apk`` ファイルをダウンロードするか、QRコードをスキャンしてインストールするか選ぶページが表示されます。インストールガイドに従ってアプリケーションのインストールを完了してください。

     また、事前にコンパイルされたAPKはこちらからダウンロードできます: :download:`RemoteRelay.apk</_static/other/RemoteRelay.apk>`

   * このアプリをGoogle Playや他のアプリマーケットにアップロードしたい場合は、 ``.aab`` ファイルを生成できます。



3. コードをアップロードする
-----------------------------

#. ``ultimate-sensor-kit\iot_project\bluetooth\08-Bluetooth_remote_relay`` のパスの下で ``08-Bluetooth_remote_relay.ino`` ファイルを開くか、このコードを **Arduino IDE** にコピーしてください。

   .. raw:: html

       <iframe src=https://create.arduino.cc/editor/sunfounder01/97039b6d-f77f-481c-a92e-c7667fc2d4cc/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

#. 適切なボードとポートを選択した後、 **書き込み** ボタンをクリックしてください。

#. シリアルモニターを開き（ボーレートを **9600** に設定）、デバッグメッセージを確認します。

4. アプリとBluetoothモジュールの接続
-----------------------------------------------

最初に作成したアプリケーションがスマートフォンにインストールされていることを確認してください。

#. まず、スマートフォンの **Bluetooth** を有効にします。

   .. image:: img/new/09-app_1_shadow.png
      :width: 60%
      :align: center

#. スマートフォンの **Bluetooth設定** に移動し、 **JDY-31-SPP** といった名前を探します。

   .. image:: img/new/09-app_2_shadow.png
      :width: 60%
      :align: center

#. 見つけたら、ポップアップウィンドウで **ペアリング** のリクエストに同意します。ペアリングコードが求められた場合は、「1234」と入力してください。

   .. image:: img/new/09-app_3_shadow.png
      :width: 60%
      :align: center

#. 新しくインストールされた **Remote Relay** アプリを開きます。

   .. image:: img/new/13-app_4_shadow.png
      :width: 25%
      :align: center

#. アプリ内で **Connect** ボタンをクリックして、アプリとBluetoothモジュール間の接続を確立します。

   .. image:: img/new/13-app_5_shadow.png
      :width: 60%
      :align: center

#. このページには、ペアリング済みのBluetoothデバイスのリストが表示されます。 ``xx.xx.xx.xx.xx.xx JDY-31-SPP`` オプションをリストから選びます。各デバイスの名前は、そのMACアドレスの隣に記載されています。

   .. image:: img/new/13-app_6_shadow.png
      :width: 60%
      :align: center

#. 上記のページにデバイスが表示されていない場合、このアプリは近くのデバイスをスキャンする権限がない可能性があります。その場合、設定を手動で調整する必要があります。

   * **APP情報** ページにアクセスするには、アプリのアイコンを長押しして選択します。または、このページに別の方法でアクセスできる場合は、それを使用します。

   .. image:: img/new/13-app_8_shadow.png
         :width: 60%
         :align: center

   * **許可** ページに移動します。

   .. image:: img/new/08-app_9_shadow.png
         :width: 60%
         :align: center

   * アプリが近くのデバイスをスキャンできるようにするには、 **近くのデバイス** に進み、 **常に** を選択します。

   .. image:: img/new/08-app_10_shadow.png
         :width: 60%
         :align: center

   * その後、アプリを再起動して、ステップ5と6を繰り返してBluetoothに成功裏に接続します。

#. 接続に成功すると、メインページにリダイレクトされます。リレーの電源を入れるか切るには、「ON」または「OFF」ボタンをクリックします。

   .. note ::
      BluetoothのMACアドレスに「1」が含まれている場合、最初の成功したBluetooth接続後にリレーが一時的にオンになります。Bluetooth接続時にMACアドレスがArduinoに送信されるため、Arduinoは「1」を検出してリレーを開きます。Bluetooth初期化後、アプリはBluetoothを介してArduinoに0を送信し、接続後にリレーの初期状態が閉じた状態になるようにします。

   .. image:: img/new/13-app_7_shadow.png
      :width: 60%
      :align: center


5. コードの説明
-----------------------------------------------

1. **ライブラリとグローバル変数の初期化**

   .. code-block:: arduino
   
       #include <SoftwareSerial.h>
   
       const int bluetoothTx = 3;                           
       const int bluetoothRx = 4;                           
       SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);
   
       const int relayPin = 8;

   この部分では ``SoftwareSerial`` ライブラリをインクルードし、グローバル変数を設定しています。ピン3とピン4はそれぞれBluetoothモジュールとのデータ送受信用に定義されています。さらに、リレーモジュールはピン8に接続されています。

2. **setup() 関数**

   .. code-block:: arduino
   
       void setup() {
         Serial.begin(9600);
         bleSerial.begin(9600);
         pinMode(relayPin, OUTPUT);
       }

   この関数は、ボーレート9600でシリアルモニターとBluetoothモジュールの通信を初期化します。また、 ``relayPin`` をOUTPUTピンとして設定しています。

3. **loop() 関数**

   .. code-block:: arduino
   
       void loop() {
         if (bleSerial.available() > 0) {
           char message = bleSerial.read();
           // Serial.println(message);  //for debug
   
           if (message == '1') {
             digitalWrite(relayPin, HIGH);
             Serial.println("On");
           } else if (message == '0') {
             digitalWrite(relayPin, LOW);
             Serial.println("Off");
           }
         }
       }

   ``loop()`` 関数は連続して実行されます。Bluetoothモジュールからメッセージが受信されたかどうかを確認します。メッセージが受信された場合、その文字を読み取ります。文字（'1'または'0'）に応じて、リレーをオンまたはオフにし、シリアルモニターに確認メッセージ（「On」または「Off」）を送信します。
