.. _fun_tof_distance_monitor:

ToF 距離モニター
==========================

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/fun/09-fun_ToF_distance_monitor.mp4"  type="video/mp4">
      ブラウザがビデオタグをサポートしていません。
   </video>

このプロジェクトは、VL53L0X 時間飛行（ToF）マイクロLIDAR距離センサーを使用して、対象物までの距離を測定し、OLEDスクリーンに表示します。測定された距離（ミリメートル単位）はシリアルモニターにも出力されます。VL53L0Xはおおよそ50mmから1200mmの範囲を測定できます。

1. 回路を組む
-----------------------------

.. image:: img/09-fun_ToF_distance_monitor_circuit.png
    :width: 90%

* :ref:`cpn_uno`
* :ref:`cpn_VL53L0X`
* :ref:`cpn_olde`


2. コード
-----------------------------

#. ``ultimate-sensor-kit\fun_project\09-ToF_distance_monitor`` のパス内の ``09-ToF_distance_monitor.ino`` ファイルを開くか、このコードを **Arduino IDE** にコピーします。

   .. raw:: html
       
       <iframe src=https://create.arduino.cc/editor/sunfounder01/8077aa45-8e0c-4c13-9211-b23926b79462/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>




3. コードの説明
-------------------------

本プロジェクトでは、VL53L0X Time of Flight（ToF）センサーを用いて、光が対象物まで到達して戻ってくるまでの時間を測定し、距離を計算します。測定した距離はミリメートル単位でOLEDディスプレイに表示されます。シリアル通信も利用して、測定値をモニタリングやデバッグのために出力します。OLEDディスプレイとVL53L0Xセンサーは、共にArduinoとI2Cプロトコルで通信します。

#. 必要なライブラリをインクルードし、コンポーネントを初期化

   .. code-block:: arduino

      #include <Wire.h>
      #include "Adafruit_VL53L0X.h"
      #include <SPI.h>
      #include <Adafruit_GFX.h>
      #include <Adafruit_SSD1306.h>
   
      // Initialize the OLED display module with a resolution of 128x64
      Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);
      
      // Initialize the VL53L0X distance sensor
      Adafruit_VL53L0X lox = Adafruit_VL53L0X();
   
   
   - I2C通信、距離センサー、SPIプロトコル、OLEDディスプレイを操作するための必要なライブラリがインクルードされています。
   - OLEDディスプレイとVL53L0X距離センサーが初期化されています。

#. シリアル通信を初期化し、ディスプレイとVL53L0X距離センサーを準備

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
      
        // Start the OLED display with I2C address 0x3C
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        display.display();
        delay(1000);
      
        // Begin I2C communication
        Wire.begin();
   
        // Start the VL53L0X distance sensor, halt if initialization fails
        if (!lox.begin()) {
          Serial.println(F("Failed to boot VL53L0X"));
          while (1)
            ;
        }
      
        // Set OLED display text size and color
        display.setTextSize(3);
        display.setTextColor(WHITE);
      }
   
   
   - 9600ボーのシリアル通信を開始。
   - OLEDディスプレイをそのI2Cアドレスで初期化。
   - I2C通信を開始。
   - VL53L0X距離センサーが正しく初期化されたか確認。もし初期化に失敗した場合、エラーメッセージを表示してArduinoは無限ループに入ります。
   - OLEDディスプレイのテキストサイズと色を設定。

#. 主なループ()：距離を測定し、結果を表示

   .. code-block:: arduino

      void loop() {
        VL53L0X_RangingMeasurementData_t measure;
      
        lox.rangingTest(&measure, false);  // pass in 'true' to get debug data printout
      
        // If there are no phase failures, display the measured distance
        if (measure.RangeStatus != 4) {
          display.clearDisplay();
          display.setCursor(12, 22);
          display.print(measure.RangeMilliMeter);
          display.print("mm");
          display.display();
          Serial.println();
          delay(50);
        } else {
          display.display();
          display.clearDisplay();
          return;
        }
      }
   
   
   - 測定データを格納する変数を作成。
   - VL53L0Xセンサーを使用して測定を実行。
   - 測定が有効であるか（すなわち、フェーズ失敗がないか）を確認。
   - 測定が有効な場合、OLEDディスプレイをクリアし、カーソルの位置を設定して、測定された距離を表示。
   - それ以外の場合、ディスプレイをリフレッシュし、次の読み取りのためにクリアします。
