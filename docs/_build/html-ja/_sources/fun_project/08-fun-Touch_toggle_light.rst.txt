.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _fun_touch_toggle_light:

タッチトグルライト
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/08-fun-Touch_toggle_light.mp4"  type="video/mp4">
      ご使用のブラウザはビデオタグをサポートしていません。
   </video>

このプロジェクトでは、タッチセンサーと信号機LEDモジュールを使って、シンプルな信号機制御メカニズムを作成します。タッチセンサーが活性化されると、LEDは次の順番で切り替わります：赤 -> 黄 -> 緑。

1. 回路の構築
-----------------------------

.. image:: img/08-fun_touch_toggle_light_circuit.png
    :width: 80%

* :ref:`cpn_uno`
* :ref:`cpn_touch`
* :ref:`cpn_traffic`


2. コード
-----------------------------

#. ``ultimate-sensor-kit\fun_project\08-Touch_toggle_light`` のパスにある ``08-Touch_toggle_light.ino`` ファイルを開くか、このコードを **Arduino IDE** にコピーペーストしてください。

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/7e6106dd-6a46-4bbb-8057-5b93d5fa25b5/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


3. コードの説明
-----------------------------

このプロジェクトは基本的な原理で動作します：タッチセンサーでタッチが検出された場合、次のLED（赤 -> 黄 -> 緑）が点灯します。現在どのLEDが活性化しているかは、変数 ``currentLED`` で管理されます。

1. ピンと初期値の定義

   .. code-block:: arduino
   
       const int touchSensorPin = 2;  // タッチセンサーのピン
       const int rledPin = 9;         // 赤LEDのピン
       const int yledPin = 8;         // 黄LEDのピン
       const int gledPin = 7;         // 緑LEDのピン
       int lastTouchState;            // タッチセンサーの前の状態
       int currentTouchState;         // タッチセンサーの現在の状態
       int currentLED = 0;            // 現在のLED 0->赤, 1->黄, 2->緑
   
   これらの行は、Arduinoボードに接続するコンポーネントのピンを定義し、タッチとLEDの状態を初期化します。

2. setup() 関数

   .. code-block:: arduino
   
       void setup() {
         Serial.begin(9600);              // シリアル通信の初期化
         pinMode(touchSensorPin, INPUT);  // タッチセンサーのピンを入力として設定
         // LEDピンを出力として設定
         pinMode(rledPin, OUTPUT);
         pinMode(yledPin, OUTPUT);
         pinMode(gledPin, OUTPUT);
         currentTouchState = digitalRead(touchSensorPin);
       }
   
   この関数は、Arduinoが電源オンまたはリセットされたときに一度だけ実行されます。ここでタッチセンサーを入力（値を読む）として設定し、LEDを出力（値を設定する）として設定します。また、デバッグを許可するシリアル通信を開始し、初期のタッチ状態を読み取ります。

3. loop() 関数

   .. code-block:: arduino
   
       void loop() {
         lastTouchState = currentTouchState;               // 最後の状態を保存
         currentTouchState = digitalRead(touchSensorPin);  // 新しい状態を読み取る
         if (lastTouchState == LOW && currentTouchState == HIGH) {
           Serial.println("センサーがタッチされました");
           turnAllLEDsOff();  // すべてのLEDを消灯
           // シーケンス内の次のLEDを点灯
           switch (currentLED) {
             case 0:
               digitalWrite(rledPin, HIGH);
               currentLED = 1;
               break;
             case 1:
               digitalWrite(yledPin, HIGH);
               currentLED = 2;
               break;
             case 2:
               digitalWrite(gledPin, HIGH);
               currentLED = 0;
               break;
           }
         }
       }
  
  メインループでは、現在のタッチ状態が前のものと比較されて読み取られます。タッチが検出された場合（LOWからHIGHへの遷移）、すべてのLEDが消灯し、シーケンス内の次のLEDが点灯します。

4. LEDを消灯する関数

   .. code-block:: arduino
      
       void turnAllLEDsOff() {
         digitalWrite(rledPin, LOW);
         digitalWrite(yledPin, LOW);
         digitalWrite(gledPin, LOW);
       }

  この関数は呼び出されたとき、すべてのLEDを消灯させるためにそのピンをLOWに設定します。

