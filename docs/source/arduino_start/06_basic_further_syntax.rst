.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

スケッチの書き方のルール
================================

もし友達に明かりをつけてもらいたい場合、"明かりをつけて。"と言ったり、"ライトオン、お願い。"と言うような口調で言うことができます。

しかし、Arduinoボードに何かを実行させたい場合は、Arduinoのプログラミング規則に従ってコマンドを入力する必要があります。

この章では、Arduino言語の基本的なルールを含んでおり、自然言語をコードに変換する方法を理解する手助けとなります。

もちろん、これは慣れるまでに時間がかかるプロセスであり、初心者にとっては最もエラーが発生しやすい部分でもあります。よって、よく間違えるのであれば気にしないで、何度か試してみてください。


セミコロン ``;``
--------------------

手紙を書くときに、各文の最後にピリオドを書くように、Arduino言語でも ``;`` を使ってボードにコマンドの終了を告げる必要があります。

お馴染みの「オンボードLEDの点滅」の例を取り上げましょう。正常なスケッチは以下のようになります。

例：

.. code-block:: arduino

    void setup() {
        // 初期設定のコードはここに記述します。一度だけ実行されます：
        pinMode(13,OUTPUT); 
    }

    void loop() {
        // メインのコードはここに記述します。これは繰り返し実行されます：
        digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
        delay(500);
    }


次に、以下の2つのスケッチを見て、それらが実行する前にArduinoに正しく認識されるかどうかを推測してみましょう。

スケッチA:

.. code-block:: arduino
    :emphasize-lines: 8,9,10,11

    void setup() {
        // 初期設定のコードはここに記述します。一度だけ実行されます：
        pinMode(13,OUTPUT); 
    }

    void loop() {
        // メインのコードはここに記述します。これは繰り返し実行されます：
        digitalWrite(13,HIGH)
        delay(500)
        digitalWrite(13,LOW)
        delay(500)
    }

スケッチB:

.. code-block:: arduino
    :emphasize-lines: 8,9,10,11,12,13,14,15,16

    void setup() {
        // 初期設定のコードはここに記述します。一度だけ実行されます：
        pinMode(13,OUTPUT);
    }
    
    void loop() {
        // メインのコードはここに記述します。これは繰り返し実行されます：
        digitalWrite(13,
    HIGH);  delay
        (500
        );
        digitalWrite(13,
        
        LOW);
                delay(500)
        ;
    }

結果として、 **スケッチA** はエラーを報告し、 **スケッチB** は実行します。

* **スケッチA** のエラーは ``;`` が不足している点であり、見た目は普通に見えますが、Arduinoはそれを読み取ることができません。
* **スケッチB** は、人間にとっては不自然に見えますが、実際には、インデントや改行、ステートメントのスペースなどはArduinoのプログラムには存在しないものなので、Arduinoのコンパイラにとっては例と同じように見えます。

しかしながら、 **スケッチB** のようにコードを書くことはお勧めしません。通常、コードを書き、閲覧するのは人間なので、自分自身を困らせないようにしてください。



波括弧 ``{}``
------------------

``{}`` はArduinoプログラミング言語の主要な要素であり、常に対で登場する必要があります。
より優れたプログラミングの慣習としては、左の波括弧を入力した直後に右の波括弧も同時に入力し、その後カーソルを波括弧の間に移動してステートメントを挿入するという方法があります。




コメント ``//``
---------------

コメントは、コンパイラが無視するスケッチの一部です。通常、プログラムがどのように動作するかを他の人に説明するために使用されます。

コードの行に隣接する2つのスラッシュを書くと、コンパイラはその行の終わりまで何も考慮しません。

新しいスケッチを作成すると、2つのコメントが含まれています。これらのコメントを削除しても、スケッチには何の影響もありません。

.. code-block:: arduino
    :emphasize-lines: 2,6

    void setup() {
        // ここに一度だけ実行するセットアップコードを入れます。
    }

    void loop() {
        // ここに繰り返し実行するメインのコードを入れます。
    }

コメントはプログラミングで非常に有用であり、以下にいくつかの一般的な用途を示します。

* 用途A：このコードのセクションが何をするのか、自分自身や他人に説明する。

.. code-block:: arduino

    void setup() {
        pinMode(13,OUTPUT); // ピン13を出力モードに設定し、オンボードLEDを制御します。
    }

    void loop() {
        digitalWrite(13,HIGH); // ピン13をHIGHに設定してオンボードLEDを点灯します。
        delay(500); // 500ms間現状を保ちます。
        digitalWrite(13,LOW); // オンボードLEDを消灯します。
        delay(500); // 500ms間現状を保ちます。
    }

* 用途B：一時的にいくつかの文を無効化（削除せずに）し、それらが必要になったときにコメントを解除する。これはコードのデバッグやプログラムエラーの特定に非常に役立ちます。

.. code-block:: arduino
    :emphasize-lines: 3,4,5,6

    void setup() {
        pinMode(13,OUTPUT);
        // digitalWrite(13,HIGH);
        // delay(1000);
        // digitalWrite(13,LOW);
        // delay(1000);
    }

    void loop() {
        digitalWrite(13,HIGH);
        delay(200);
        digitalWrite(13,LOW);
        delay(200);
    }    

.. note::
    ショートカット ``Ctrl+/`` を使って、コードを素早くコメントアウトまたはコメント解除できます。




コメント ``/**/``
------------------

この ``/**/`` 形式のコメントも ``//`` と同様にコメントを表現しますが、複数行にわたることができます。コンパイラが ``/*`` を読み取ると、 ``*/`` に遭遇するまで後続のすべてを無視します。

例1：

.. code-block:: arduino
    :emphasize-lines: 1,8,9,10,11

    /* 点滅 */

    void setup() {
        pinMode(13,OUTPUT);
    }

    void loop() {
        /*
        以下のコードはオンボードLEDを点滅させます。
        delay()内の数値を変更することで、点滅の頻度を調整できます。
        */
        digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
        delay(500);
    }



``#define``
--------------

これは便利なC++のツールです。

.. code-block:: arduino

    #define identifier token-string

コンパイラは、 ``identifier`` を読み取ると自動的に ``token-string`` に置き換えます。これは通常、定数の定義に使用されます。

例として、defineを使用してコードの可読性を向上させたスケッチを以下に示します。

.. code-block:: arduino
    :emphasize-lines: 1,2

    #define ONBOARD_LED 13
    #define DELAY_TIME 500

    void setup() {
        pinMode(ONBOARD_LED,OUTPUT);
    }

    void loop() {
        digitalWrite(ONBOARD_LED,HIGH);
        delay(DELAY_TIME);
        digitalWrite(ONBOARD_LED,LOW);
        delay(DELAY_TIME);
    }

コンパイラにとって、実際には以下のように見えます。

.. code-block:: arduino

    void setup() {
        pinMode(13,OUTPUT);
    }

    void loop() {
        digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
        delay(500);
    }

``識別子`` がプログラム内で置き換えられていないことがわかります。
したがって、使用する際にいくつかの注意点があります。

1. ``トークン文字列`` は手動でのみ変更でき、プログラム内で算術によって他の値に変換することはできません。

2. ``;`` などの記号の使用を避けてください。例：

.. code-block:: arduino
    :emphasize-lines: 1

    #define ONBOARD_LED 13;

    void setup() {
        pinMode(ONBOARD_LED,OUTPUT);
    }

    void loop() {
        digitalWrite(ONBOARD_LED,HIGH);
    }

コンパイラは次のように認識し、エラーとして報告されます。

.. code-block:: arduino
    :emphasize-lines: 2,6

    void setup() {
        pinMode(13;,OUTPUT);
    }

    void loop() {
        digitalWrite(13;,HIGH);
    }

.. note:: 
    ``#define`` での命名規則として、変数との混同を避けるために ``identifier`` を大文字にするのが一般的です。
