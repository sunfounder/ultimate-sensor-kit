.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _c201_connect_blynk:

1.3 R4 ボードを Blynk に接続する
====================================

#. ESPC2-01 モジュールを Arduino Uno R4 Minima に接続します。

   .. note::

      モジュールは起動時に大きな電流を引きます。9V 電池または外部電源を R4 Minima
      の DC ジャックに必ず接続してください。

   .. image:: ../img/wiring_r4_espc201.png
      :width: 80%

#. ``00-Blynk_quick_start.ino`` を ``ultimate-sensor-kit\code\iot_project_espc201\wifi\00-Blynk_quick_start`` から開きます。

#. 次の 3 行を、お使いのアカウントの **Device** ページからコピーした内容に置き換え
   ます。この 3 行が、ボードがどの Blynk アカウントに属するかを決めます。

   .. code-block:: arduino

      #define BLYNK_TEMPLATE_ID   "TMPLxxxxxx"
      #define BLYNK_TEMPLATE_NAME "Ultimate Sensor Kit"
      #define BLYNK_AUTH_TOKEN    "YourAuthToken"

   .. image:: ../img/blynk_copy_token.png
      :width: 80%

#. 使用する Wi-Fi ネットワークの ``ssid`` と ``password`` を入力します。

   .. code-block:: arduino

      char ssid[] = "your_ssid";
      char pass[] = "your_password";

#. スケッチを書き込み、シリアルモニターを開いてボーレートを **115200** にします。
   ボードが Blynk クラウドに到達すると ``Ready`` と表示されます。

   .. image:: ../img/blynk_connect_network.png
      :width: 80%

   .. note::

      ``ESP is not responding`` と出た場合は、次を確認してください。

      * 外部電源が接続されているか
      * モジュールがアダプターにしっかり挿さり、IO9 が未接続のままか
      * R4 ボードのリセットボタンを押す

      2〜3 回試すとうまくいくことがあります。

#. Blynk.Console のデバイス状態が **offline** から **online** に変わります。

   .. image:: ../img/blynk_online.png
      :width: 70%

これでボードは接続されました。次の章から最初のプロジェクトが始まります。
