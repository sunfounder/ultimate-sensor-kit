.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _cpn_uno:

Arduino UNO R4 Minima ボード
================================

.. image:: img/36_uno_r4.webp
    :width: 600
    :align: center

**Arduino UNO R4 Minima** は、Renesas社のRA4M1（|link_ra4m1_datasheet|）マイクロコントローラーを基盤とした開発ボードで、クラシックなUNO形状を持っています。以前のバージョンよりも高速で、メモリも豊富です。DAC、RTC、HIDといった組み込み機能が多数あります。UNO R4 Minimaは、 **5V専用ボード** です。14個のデジタルI/O、最大14ビット解像度の6つのアナログ入力、48MHzのクロック速度、32kBのSRAM、256kBのフラッシュメモリ、8kBのEEPROMが搭載されています。

**技術仕様**

.. raw:: html

   <style type="text/css">
   .tg  {border-collapse:collapse;border-spacing:0;}
   .tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
     overflow:hidden;padding:10px 5px;word-break:normal;}
   .tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
     font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
   .tg .tg-fymr{border-color:inherit;font-weight:bold;text-align:left;vertical-align:top}
   .tg .tg-0pky{border-color:inherit;text-align:left;vertical-align:top}
   </style>
   <table class="tg">
   <thead>
     <tr>
       <th class="tg-fymr">ボード</th>
       <th class="tg-fymr">名前</th>
       <th class="tg-fymr">Arduino® UNO R4 Minima</th>
     </tr>
   </thead>
   <tbody>
     <tr>
       <td class="tg-0pky">マイクロコントローラ</td>
       <td class="tg-0pky" colspan="2">Renesas RA4M1 (Arm® Cortex®-M4)</td>
     </tr>
     <tr>
       <td class="tg-0pky">USB</td>
       <td class="tg-0pky">USB-C®</td>
       <td class="tg-0pky">プログラミングポート</td>
     </tr>
     <tr>
       <td class="tg-0pky">Pins</td>
       <td class="tg-0pky">Digital I/O Pins</td>
       <td class="tg-0pky">14</td>
     </tr>
     <tr>
       <td class="tg-0pky" rowspan="3">Pins</td>
       <td class="tg-0pky">Analog input pins</td>
       <td class="tg-0pky">6</td>
     </tr>
     <tr>
       <td class="tg-0pky">DAC</td>
       <td class="tg-0pky">1</td>
     </tr>
     <tr>
       <td class="tg-0pky">PWM pins</td>
       <td class="tg-0pky">6</td>
     </tr>
     <tr>
       <td class="tg-0pky" rowspan="4">通信</td>
       <td class="tg-0pky">UART</td>
       <td class="tg-0pky">Yes, 1x</td>
     </tr>
     <tr>
       <td class="tg-0pky">I2C</td>
       <td class="tg-0pky">Yes, 1x</td>
     </tr>
     <tr>
       <td class="tg-0pky">SPI</td>
       <td class="tg-0pky">Yes, 1x</td>
     </tr>
     <tr>
       <td class="tg-0pky">CAN</td>
       <td class="tg-0pky">Yes 1 CAN Bus</td>
     </tr>
     <tr>
       <td class="tg-0pky" rowspan="3">電源</td>
       <td class="tg-0pky">動作電圧</td>
       <td class="tg-0pky">5 V</td>
     </tr>
     <tr>
       <td class="tg-0pky">入力電圧（VIN）</td>
       <td class="tg-0pky">6-24 V</td>
     </tr>
     <tr>
       <td class="tg-0pky">I/OピンあたりのDC電流</td>
       <td class="tg-0pky">8 mA</td>
     </tr>
     <tr>
       <td class="tg-0pky">クロック速度</td>
       <td class="tg-0pky">メインコア</td>
       <td class="tg-0pky">48 MHz</td>
     </tr>
     <tr>
       <td class="tg-0pky">メモリ</td>
       <td class="tg-0pky">RA4M1</td>
       <td class="tg-0pky">256 kB Flash, 32 kB RAM</td>
     </tr>
     <tr>
       <td class="tg-0pky" rowspan="2">寸法</td>
       <td class="tg-0pky">幅</td>
       <td class="tg-0pky">68.85 mm</td>
     </tr>
     <tr>
       <td class="tg-0pky">長さ</td>
       <td class="tg-0pky">53.34 mm</td>
     </tr>
   </tbody>
   </table>
   <br/><br/>


**その他**

* `Arduino IDE <https://www.arduino.cc/en/software>`_
* :ref:`install_arduino`
* `Arduinoプログラミング言語リファレンス <https://www.arduino.cc/reference/en/>`_
* |link_uno_r4|
* |link_r4_datasheet|
* |link_ra4m1_datasheet|
