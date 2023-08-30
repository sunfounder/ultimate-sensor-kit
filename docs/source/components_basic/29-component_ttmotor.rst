.. _cpn_ttmotor:

TTモーター
==========================

.. image:: img/29_tt_motor.jpg
    :width: 400
    :align: center

.. raw:: html
    
    <br/>

概要
---------------------------
TTモーターは、ギアボックスが取り付けられた直流モーターの一種です。このギアボックスは、モーターの回転数を低減させ、トルクを増大させます。TTモーターは、車輪、プロペラ、扇風機などを駆動する用途でよく使用されます。TTモーターは赤と黒の2本のワイヤーがあり、通常、赤がプラス、黒がマイナスです。

製品には1:48のギア比を持つTT DCギアボックスモーターが使用されており、200mmのワイヤー2本が0.1インチのオスコネクターで付属しています。これにより、ブレッドボードまたはターミナルブロックに容易に接続できます。電源は3〜6VDCで、高電圧でより速く動作します。

原理
---------------------------
TTモーターは電気エネルギーを機械エネルギーに変換する仕組みです。モーターのワイヤーに電圧を印加すると、磁場が発生してモーターが回転します。モーターの速度と回転方向は、供給される電源の電圧と極性に依存します。電圧が高いほど、モーターは速く回転します。極性を逆にすると、モーターは逆方向に回転します。

使い方
---------------------------

**使用する電子部品**

- Arduino Uno R4 または R3 ボード * 1
- TTモーター * 1
- ジャンパーワイヤー

**回路の組み立て**

.. image:: img/29_tt_motor_circuit.png
    :width: 400
    :align: center

.. raw:: html
    
    <br/><br/>   

コード
^^^^^^^^^^^^^^^^^^^^

.. raw:: html
    
    <iframe src=https://create.arduino.cc/editor/sunfounder01/045d66e3-280d-4ef8-aa96-a1770ade414f/preview?embed style="height:510px;width:100%;margin:10px 0" frameborder=0></iframe>


.. raw:: html

   <video loop autoplay muted style = "max-width:100%">
      <source src="../_static/video/basic/29-component_ttmotor.mp4"  type="video/mp4">
      ご使用のブラウザはこのビデオタグに対応していません。
   </video>
   <br/><br/>  

コードの説明
^^^^^^^^^^^^^^^^^^^^

1. コードの最初の部分では、モーター制御用のピンが定義されています。これらはL9110モーター制御ボードに接続されます。

   .. code-block:: arduino
   
      // モーターピンの定義
      const int motorB_1A = 9;
      const int motorB_2A = 10;

2. ``setup()`` 関数は、 ``pinMode()`` 関数を使用してモーター制御ピンを出力として初期化します。その後、 ``analogWrite()`` を使用してモーターの速度を設定します。 ``analogWrite()`` に渡す値は0（オフ）から255（全速）までです。次に、 ``delay()`` 関数でコードを5000ミリ秒（または5秒）一時停止させ、その後でモーターの速度を0（オフ）に設定します。

   .. code-block:: arduino
   
      void setup() {
        pinMode(motorB_1A, OUTPUT);  // set motor pin 1 as output
        pinMode(motorB_2A, OUTPUT);  // set motor pin 2 as output
   
        analogWrite(motorB_1A, 255);  // set motor speed (0-255)
        analogWrite(motorB_2A, 0);
   
        delay(5000);
   
        analogWrite(motorB_1A, 0);  
        analogWrite(motorB_2A, 0);
      }

追加のアイディア
^^^^^^^^^^^^^^^^^^^^

- ポテンショメーターでモーター速度を制御：モーターの速度を固定する代わりに、ポテンショメーターを使用して動的に速度を制御できます。
