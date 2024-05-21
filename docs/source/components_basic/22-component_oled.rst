.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _cpn_olde:

OLEDディスプレイモジュール
==========================

.. image:: img/22_OLED.png
    :width: 300
    :align: center

はじめに
---------------------------
OLED（Organic Light-Emitting Diode）ディスプレイモジュールは、有機材料を用いて電流が流れると発光する薄く、柔軟なスクリーン上にテキスト、グラフィック、画像を表示できるデバイスです。

OLEDディスプレイの最大の特長は、自ら発光するため、別のバックライト源が不要であることです。このため、LCDディスプレイと比較して、OLEDはより高いコントラスト、明るさ、視野角を持っています。

さらに、OLEDディスプレイは「深い黒」を再現する能力もあります。各ピクセルが独自に発光するため、黒色を表示する際には該当ピクセルをオフにできます。

低い消費電力（点灯しているピクセルのみが電流を消費）もあり、スマートウォッチやヘルストラッカー、その他のウェアラブルデバイスでよく使用されています。

原理
---------------------------
OLEDディスプレイモジュールは、OLEDパネルとその裏面に取り付けられたOLEDドライバーチップから構成されます。OLEDパネルは、さまざまな色の光を発生させることができる多くの小さなピクセルで構成されています。各ピクセルは、二つの電極（アノードとカソード）の間に挟まれた数層の有機材料から成り立っています。電流が電極を流れると、有機材料がその組成に応じて異なる波長の光を発光します。

OLEDドライバーチップは、I2C（Inter-Integrated Circuit）と呼ばれるシリアル通信プロトコルを用いてOLEDパネルのピクセルを制御できるチップです。

このドライバーチップは、Arduinoからの信号をOLEDパネルへのコマンドに変換します。Arduinoは、I2Cプロトコルを制御できるライブラリを用いて、OLEDドライバーチップにデータを送信できます。その一例がAdafruit SSD1306ライブラリ1です。このライブラリを使用すれば、OLEDディスプレイモジュールを初期化したり、明るさを設定したり、テキストやグラフィック、画像を表示したりできます。

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4またはR3ボード * 1
- OLEDディスプレイモジュール * 1
- ジャンパーワイヤ

**回路の組立て**

.. image:: img/22_OLED_circuit.png
    :width: 600
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. note:: 
   ライブラリのインストールには、Arduinoライブラリマネージャーで **"Adafruit SSD1306"** と **"Adafruit GFX"** を検索してインストールしてください。

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/fee9cc72-22bb-408c-81cf-fb4589121276/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/22-component_oled.mp4"  type="video/mp4">
      Your browser does not support the video tag.
   </video>
   <br/><br/>  

コードの解説
^^^^^^^^^^^^^^^^^^^^

1. **ライブラリのインクルードと初期定義**：

   OLEDとのインターフェースに必要なライブラリがインクルードされ、その後でOLEDの寸法やI2Cアドレスに関する定義が行われます。

   - **Adafruit SSD1306**: SSD1306 OLEDディスプレイとのインターフェースを補助するライブラリです。ディスプレイの初期化、設定の制御、コンテンツの表示に関するメソッドが提供されています。
   - **Adafruit GFX Library**: OLEDを含む各種スクリーンでテキストを表示、色を生成、形を描くなどを行う基本的なグラフィックスライブラリです。

   .. note:: 
      ライブラリのインストールには、Arduinoライブラリマネージャーで **"Adafruit SSD1306"** と **"Adafruit GFX"** を検索してインストールしてください。 

   .. code-block:: arduino
    
      #include <SPI.h>
      #include <Wire.h>
      #include <Adafruit_GFX.h>
      #include <Adafruit_SSD1306.h>

      #define SCREEN_WIDTH 128
      #define SCREEN_HEIGHT 64

      #define OLED_RESET -1
      #define SCREEN_ADDRESS 0x3C

2. **ビットマップデータ**：

   OLEDスクリーン上でカスタムアイコンを表示するためのビットマップデータです。このデータは、OLEDが解釈できる形式で画像を表現しています。

   このオンラインツール |link_image2cpp| を使用して、画像を配列に変換することができます。

   ``PROGMEM`` キーワードは、配列がArduinoのマイクロコントローラのプログラムメモリに格納されることを示しています。大量のデータをRAMではなくプログラムメモリ（PROGMEM）に格納することで、RAMのスペースを節約することができます。

   .. code-block:: arduino

      static const unsigned char PROGMEM sunfounderIcon[] = {...};

3. **セットアップ関数（初期化と表示）**：

   ``setup()`` 関数は、OLEDを初期化し、いくつかのパターン、テキスト、アニメーションを表示します。

   .. code-block:: arduino

      void setup() {
         ...  // Serial initialization and OLED object initialization
         ...  // Displaying various text, numbers, and animations
      }


追加のアイデア
^^^^^^^^^^^^^^^^^^^^

- ボタンを使って表示されるメッセージを変更したり、異なるパターンやアニメーションを切り替えたりします。

- センサーの読み取り値（例：温度や湿度）をリアルタイムでOLEDに表示します。

さらに多くのプロジェクト
---------------------------
* :ref:`fun_heartrate_monitor`
* :ref:`fun_tof_distance_monitor`
* :ref:`iot_Bluetooth_oled`

