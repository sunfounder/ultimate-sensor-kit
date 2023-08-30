.. _cpn_max30102:

脈拍酸素計および心拍数センサー（MAX30102）
===============================================================

.. image:: img/15_gy_max30102_module.png
    :width: 300
    :align: center

概要
---------------------------
MAX30102は、脈拍酸素計と心拍数モニターを一体化したセンサーです。この光学センサーは、赤色と赤外線の二つのLEDから発される光の波長を用いて、脈動する血液の吸光度を光検出器で測定します。この特定のLEDカラーの組み合わせは、指先でデータを簡単に読み取ることができるように設計されています。

原理
---------------------------
MAX30102は、指や耳たぶ（または、皮膚が厚すぎない場所）に両方の光を照射し、光検出器を用いて反射光の量を測定する仕組みです。この光による脈拍検出法は、光電容積脈波図（Photoplethysmogram）と呼ばれています。

MAX30102の動作は大きく二つに分けられます：心拍数の測定と脈拍酸素計（血中の酸素レベルを測定）。

心拍数の測定
^^^^^^^^^^^^^^^^^^^^^^^^^^
動脈血中の酸素飽和度の高いヘモグロビン（HbO2）は、赤外線（IR）を吸収する特性があります。血の赤み（ヘモグロビンの量）が高いほど、赤外線は多く吸収されます。心拍ごとに血液が指を通過する際、反射される光の量が変化し、これが光検出器の出力で変動する波形を生み出します。

脈拍酸素計
^^^^^^^^^^^^^^^^^^^^
脈拍酸素計は、血中の酸素量に応じて吸収される赤色と赤外線の光の量が異なるという原理に基づいています。

使用方法
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- 脈拍酸素計および心拍数センサー（MAX30102）* 1
- ジャンパーワイヤー


**回路の組み立て**

.. image:: img/15_gy_max30102_module_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. warning::
    このスケッチは光学的な方法で心拍数を検出します。この方法は誤読を引き起こす可能性がありますので、医療診断には **使用しないでください** 。

.. note:: 
   ライブラリをインストールするには、Arduinoライブラリマネージャーで  **"SparkFun MAX3010x"** と検索し、インストールしてください。

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/8fd9aa35-11df-477e-87ea-879172104d03/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>

.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/15-component_max30102.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

1. **ライブラリのインクルードとグローバル変数の初期化**:

   必要なライブラリがインポートされ、センサーオブジェクトが生成され、データ管理のためのグローバル変数が設定されます。

   .. note:: 
      ライブラリをインストールするには、Arduinoライブラリマネージャーで **"SparkFun MAX3010x"** と検索し、インストールしてください。

   .. code-block:: arduino
    
      #include <Wire.h>
      #include "MAX30105.h"
      #include "heartRate.h"
      MAX30105 particleSensor;
      // ... (other global variables)

2. **setup()関数とセンサーの初期化**:

   シリアル通信は9600のボーレートで初期化されます。センサーとの接続が確認されたら、初期化処理が実行されます。センサーが検出されない場合はエラーメッセージが表示されます。

   .. code-block:: arduino

      void setup() {
        Serial.begin(9600);
        if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
          Serial.println("MAX30102 not found.");
          while (1) ;  // Infinite loop if sensor not detected.
        }
        // ... (further setup)

3. **赤外線値の読み取りと心拍の確認**:

   センサーから取得した赤外線の値が血流を示しています。この値に基づいて、``checkForBeat()``関数は心拍が検出されたかどうかを評価します。

   .. code-block:: arduino

      long irValue = particleSensor.getIR();
      if (checkForBeat(irValue) == true) {
          // ... (heartbeat detected actions)
      }

4. **分間心拍数（BPM）の計算**:

   心拍が検出された場合、最後に検出された心拍からの時間差に基づいてBPMが計算されます。コードは、BPMが現実的な範囲内にあるか確認し、その後で平均を更新します。

   .. code-block:: arduino

      long delta = millis() - lastBeat;
      beatsPerMinute = 60 / (delta / 1000.0);
      if (beatsPerMinute < 255 && beatsPerMinute > 20) {
          // ... (store and average BPM)
      }

5. **シリアルモニターへの値の出力**:

   赤外線の値、現在のBPM、および平均BPMがシリアルモニターに出力されます。さらに、赤外線値が低すぎる場合、指がない可能性があると警告されます。

   .. code-block:: arduino

      //Print the IR value, current BPM value, and average BPM value to the serial monitor
      Serial.print("IR=");
      Serial.print(irValue);
      Serial.print(", BPM=");
      Serial.print(beatsPerMinute);
      Serial.print(", Avg BPM=");
      Serial.print(beatAvg);

      if (irValue < 50000)
        Serial.print(" No finger?");

追加のアイデア
^^^^^^^^^^^^^^^^^^^^

- 検出された心拍ごとにLEDを点滅させる  
- 小型のOLEDまたはLCDスクリーンを使用して、リアルタイムのBPM値などの関連データを表示する。

その他のプロジェクト
---------------------------
* :ref:`fun_heartrate_monitor`
