.. _cpn_flame:

炎センサーモジュール
==========================

.. image:: img/03_flame_module.jpg
    :width: 400
    :align: center

概要
---------------------------
炎センサーは、火災や炎の存在を検出するためのセンサーです。主に火や炎が放つ赤外線を感知することで火災を検出します。家庭や産業用の火災検出システムで広く使用されています。

原理
---------------------------
炎センサーは赤外線（IR）検出の原理に基づいて動作します。センサーには、炎が放出する赤外線を検出するIRレシーバーが搭載されています。火が燃えるときにはわずかな赤外線が放出され、この光はセンサーモジュール上のフォトダイオード（IRレシーバー）によって受信されます。その後、オペアンプを使用してIRレシーバーの電圧に変化があるかどうかを確認し、火災が検出された場合には出力ピン（DO）が0V（LOW）を出力し、火災がない場合には出力ピンが5V（HIGH）を出力します。

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- 炎センサーモジュール * 1
- ジャンパーワイヤー

**回路組み立て**

.. image:: img/03_flame_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html

   <iframe src=https://create.arduino.cc/editor/sunfounder01/7529b311-3763-4b62-aa1c-a63e41871856/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/03-component_flame.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

1. コードの最初の行は、炎センサーピンの定数整数宣言です。デジタルピン7を使用して炎センサーからの出力を読み取ります。

   .. code-block:: arduino
   
      const int sensorPin = 7;

2. ``setup()`` 関数では、炎センサーピンを入力として、組み込みLEDピンを出力として初期化します。また、シリアルモニターでメッセージを表示するために、ボーレート9600でシリアル通信を開始します。

   .. code-block:: arduino
   
      void setup() {
        pinMode(sensorPin, INPUT);     // Set the flame sensor pin as input
        pinMode(LED_BUILTIN, OUTPUT);  // Set the built-in LED pin as output
        Serial.begin(9600);            // Initialize the serial monitor at a baud rate of 9600
      }

3. ``loop()`` 関数では、炎センサーの状態を連続的に確認します。センサーが炎を検出した場合、組み込みLEDが点灯し、シリアルモニターにメッセージが表示されます。炎が検出されなかった場合、LEDは消灯し、別のメッセージが表示されます。このプロセスは100ミリ秒ごとに繰り返されます。

   .. code-block:: arduino
   
      void loop() {
        // Check if the sensor is detecting a fire
        if (digitalRead(sensorPin) == 0) {
          digitalWrite(LED_BUILTIN, HIGH);  // Turn on the built-in LED
          Serial.println("** Fire detected!!! **");
        } else {
          digitalWrite(LED_BUILTIN, LOW);  // Turn off the built-in LED
          Serial.println("No Fire detected");
        }
        delay(100);
      }

追加のアイデア
^^^^^^^^^^^^^^^^

- 火災が検出された場合にブザーを鳴らすか、アラームを発生させるコードを追加してください。

- 炎センサーに加えて、煙センサーを組み込むことで、火災検出能力を高めます。

- デジタルのHIGH/LOWだけでなく、 **アナログ出力** もプロットしてみてください。 **AO** ピンを使用します。

その他のプロジェクト
---------------------------
* :ref:`iot_Flame`

