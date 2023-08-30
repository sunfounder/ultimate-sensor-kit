.. _fun_smart_trashcan:

スマートゴミ箱
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/01-fun_Smart_trashcan.mp4"  type="video/mp4">
      お使いのブラウザはビデオタグをサポートしていません。
   </video>

このプロジェクトはスマートゴミ箱のコンセプトを中心に展開されます。主な目的は、物体が一定の距離（この場合は20cm）以内に近づいたらゴミ箱の蓋が自動的に開くようにすることです。この機能は、超音波距離センサーとサーボモーターを組み合わせて実現しています。物体とセンサーとの距離は継続的に測定され、物体が十分に近づいた場合にはサーボモーターが作動して蓋を開きます。

1. 回路の構築
-----------------------------

.. image:: img/01-fun_Smart_trashcan_circuit.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_ultrasonic`
* :ref:`cpn_servo`


2. コード
-----------------------------

#. ``ultimate-sensor-kit\fun_project\01-Smart_trashcan`` のパス内にある ``01-Smart_trashcan.ino`` ファイルを開くか、このコードを **Arduino IDE** にコピーします。

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/0e371717-97dc-43ad-bdc2-e468589da2a0/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

3. コードの説明
-----------------------------

このプロジェクトは、物体とゴミ箱との距離をリアルタイムで監視するものです。超音波センサーがこの距離を連続的に測定し、物体が20cm以内に近づいた場合、ゴミ箱はそれを廃棄の意志と解釈し、自動的に蓋を開きます。この自動化により、通常のゴミ箱がスマートで便利なものとなります。

#. **初期設定と変数宣言**

   ここでは、 ``Servo`` ライブラリをインクルードし、使用する定数と変数を定義します。サーボと超音波センサーのピンが宣言され、三つの距離測定を保持する配列 ``averDist`` もあります。

   .. code-block:: arduino
       
      #include <Servo.h>
      Servo servo;
      const int servoPin = 9;
      const int openAngle = 0;
      const int closeAngle = 90;
      const int trigPin = 5;
      const int echoPin = 6;
      long distance, averageDistance;
      long averDist[3];
      const int distanceThreshold = 20;

#. setup()関数

   ``setup()`` 関数では、シリアル通信を初期化し、超音波センサーのピンを設定し、サーボを閉じた位置に初期設定します。

   .. code-block:: arduino
   
      void setup() {
        Serial.begin(9600);
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
        servo.attach(servoPin);
        servo.write(closeAngle);
        delay(100);
      }

#. loop()関数

   ``loop()`` 関数は、距離を継続的に測定し、その平均を計算し、この平均距離に基づいてゴミ箱の蓋を開けるか閉じるかを決定します。

   .. code-block:: arduino
   
      void loop() {
        for (int i = 0; i <= 2; i++) {
          distance = readDistance();
          averDist[i] = distance;
          delay(10);
        }
        averageDistance = (averDist[0] + averDist[1] + averDist[2]) / 3;
        Serial.println(averageDistance);
        if (averageDistance <= distanceThreshold) {
          servo.write(openAngle);
          delay(3500);
        } else {
          servo.write(closeAngle);
          delay(1000);
        }
      }

#. 距離測定関数

   この関数、 ``readDistance()`` は超音波センサーと実際に対話します。パルスを送信し、エコーを待ちます。そのエコーの時間は、センサーとその前の物体との距離を計算するために使用されます。

   :ref:`cpn_ultrasonic_principle` で超音波センサーの原理を参照できます。

   .. code-block:: arduino
   
      float readDistance() {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        float distance = pulseIn(echoPin, HIGH) / 58.00;
        return distance;
      }

