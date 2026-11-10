.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

.. _burn_firmware:

ESP8266モジュールのファームウェアを再書き込む方法
========================================================

R4でファームウェアを再書き込む
---------------------------------------------

**1. 回路を組む**

ESP8266とArduino UNO R4ボードを接続します。

    .. image:: img/faq_at_burn_bb.jpg
        :width: 100%

**2. R4に以下のコードをアップロード**

.. code-block:: Arduino

    void setup() {
        Serial.begin(115200);
        Serial1.begin(115200);
    }

    void loop() {
        if (Serial.available()) {      // If anything comes in Serial (USB),
            Serial1.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
        }
            if (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
            Serial.write(Serial1.read());   // read it and send it out Serial (USB)
        }
    }

**3. ファームウェアの書き込み**

* **Windows** を使用している場合は、以下の手順でファームウェアを書き込みます。

    #. ファームウェアと書き込みツールをダウンロード。

        * :download:`ESP8266 Firmware <https://raw.githubusercontent.com/sunfounder/ultimate-sensor-kit/main/iot_project/esp8266_firmware.zip>`

    #. 解凍後、4つのファイルが表示されます。

       .. image:: img/bat_firmware.png
   
       * ``BAT_AT_V1.7.1.0_1M.bin``: ESP8266モジュールに書き込むファームウェア。
       * ``esptool.exe``: Windows用のコマンドラインユーティリティ。
       * ``install_r3.bat``: Windowsシステム用のコマンドパッケージ。このファイルをダブルクリックすると、ファイル内のすべてのコマンドが実行されます。
       * ``install_r4.bat``: ``install_r3.bat`` と同様ですが、UNO R4ボード専用です。

       .. raw:: html

            <br/>

    #. ``install_r4.bat`` をダブルクリックしてファームウェアの書き込みを開始します。以下のプロンプトが表示された場合、ファームウェアは正常にインストールされています。

       .. image:: img/install_firmware.png

       .. note::
           書き込みに失敗した場合は、以下の点を確認してください。

           * ESP8266モジュールのRSTをGNDに挿入してから外します。
           * 配線が正確であることを確認します。
           * コンピュータがボードを正しく認識しているか、またポートが占有されていないかを確認します。
           * install.batファイルを再度開きます。

* **Mac OS** を使用している場合、以下の手順でファームウェアを書き込みます。

    #. 以下のコマンドでEsptoolをインストールします。EsptoolはPythonベースの、オープンソースでプラットフォームに依存しないEspressifチップのROMブートローダーと通信するユーティリティです。

       .. code-block::

           python3 -m pip install --upgrade pip
           python3 -m pip install esptool

    #. Esptoolが正常にインストールされていれば、 ``python3 -m esptool`` を実行すると[usage: esptool]というメッセージが出力されます。

    #. ファームウェアをダウンロードします。

       * :download:`ESP8266 Firmware <https://raw.githubusercontent.com/sunfounder/ultimate-sensor-kit/main/iot_project/esp8266_firmware.zip>`

    #. 解凍後、4つのファイルが表示されます。

       .. image:: img/bat_firmware.png

       * ``BAT_AT_V1.7.1.0_1M.bin``: ESP8266モジュールに書き込むファームウェア。
       * ``esptool.exe``: Windows用のコマンドラインユーティリティ。
       * ``install_r3.bat``: Windowsシステム用のコマンドパッケージ。
       * ``install_r4.bat``: ``install_r3.bat`` と同様ですが、UNO R4ボード専用です。

       .. raw:: html

            <br/>

    #. ターミナルを開き、ダウンロードしたファームウェアのフォルダに移動した後、以下のコマンドを実行して既存のファームウェアを消去し、新しいファームウェアを再書き込みます。

       .. code-block::

           python3 -m esptool --chip esp8266 --before no_reset_no_sync erase_flash
           python3 -m esptool --chip esp8266 --before no_reset_no_sync write_flash 0 "BAT_AT_V1.7.1.0_1M.bin"

    #. 以下のプロンプトが表示された場合、ファームウェアは正常にインストールされています。

       .. image:: img/install_firmware_macos.png

       .. note::
           書き込みに失敗した場合は、以下の点を確認してください。

           * ESP8266アダプターのRSTをGNDに挿入してから抜いて、ESP8266モジュールをリセットします。
           * 配線が正しいかどうかを確認してください。
           * コンピュータがあなたのボードを適切に認識していること、そしてポートが占有されていないことを確認してください。
           * install.batファイルを再度開きます。


**4. テスト**

#. 元の配線に基づいて、IO1を3V3に接続します。

   .. image:: img/faq_at_burn_check_bb.jpg
       :width: 800
   
   .. raw:: html

     <br/><br/>

#. 上部右隅にある虫眼鏡アイコン（シリアルモニター）をクリックし、ボーレートを **115200** に設定すると、ESP8266モジュールに関する情報が表示されます。

   .. image:: img/sp20220524113020.png

   .. note::

       * ``ready`` が表示されない場合は、ESP8266モジュールをリセット（RSTをGNDに接続）して、シリアルモニターを再度開きます。

#. **NEWLINE DROPDOWN BOX** をクリックして、ドロップダウンオプションで ``both NL & CR`` を選択し、 ``AT`` を入力します。OKが返された場合、ESP8266はR3ボードと正常に接続されたことを意味します。

   .. image:: img/sp20220524113702.png 

これで、 :ref:`config_esp8266` に従って、ESP8266モジュールの動作モードとボーレートを設定することができます。





R3でファームウェアを再書き込み
---------------------------------------

**1. 回路を組む**

ESP8266とSunFounder R3ボードを接続します。

    .. image:: img/connect_esp8266.png
        :width: 800

**2. ファームウェアの書き込み**

* **Windows** を使用している場合は、以下の手順でファームウェアを書き込みます。

    #. ファームウェアと書き込みツールをダウンロードします。

       * :download:`ESP8266 Firmware <https://raw.githubusercontent.com/sunfounder/ultimate-sensor-kit/main/iot_project/esp8266_firmware.zip>`

    #. 解凍した後、4つのファイルが表示されます。

       .. image:: img/bat_firmware.png

       * ``BAT_AT_V1.7.1.0_1M.bin``: ESP8266モジュールに書き込むためのファームウェア。
       * ``esptool.exe``: Windows用のコマンドラインユーティリティ。
       * ``install_r3.bat``: Windowsシステム用のコマンドパッケージ。このファイルをダブルクリックすると、ファイル内のすべてのコマンドが実行されます。
       * ``install_r4.bat``: ``install_r3.bat`` と同じですが、UNO R4ボード専用です。

       .. raw:: html

            <br/>


    #. ``install_r3.bat`` をダブルクリックして、ファームウェアの書き込みを開始します。次のプロンプトが表示されたら、ファームウェアのインストールは成功です。

       .. image:: img/install_firmware.png

       .. note::
           書き込みに失敗した場合は、以下の点を確認してください。

           * ESP8266モジュールをリセットします（ESP8266アダプタのRSTをGNDに挿入し、その後抜きます）。
           * 配線が正しいか確認します。
           * コンピュータがボードを正しく認識しているか、また、ポートが使用中でないか確認します。
           * install.batファイルを再度開きます。

* **Mac OS** システムを使用している場合は、以下の手順でファームウェアを書き込みます。

    #. Esptoolをインストールするための以下のコマンドを使用します。EsptoolはPythonベースのオープンソース、プラットフォームに依存しないEspressifチップのROMブートローダーと通信するユーティリティです。

       .. code-block::

           python3 -m pip install --upgrade pip
           python3 -m pip install esptool

    #. Esptoolが正しくインストールされた場合、 ``python3 -m esptool`` を実行すると[usage: esptool]というメッセージが出力されます。

    #. ファームウェアをダウンロードします。

       * :download:`ESP8266 Firmware <https://raw.githubusercontent.com/sunfounder/ultimate-sensor-kit/main/iot_project/esp8266_firmware.zip>`

    #. 解凍すると、3つのファイルが表示されます。

       .. image:: img/bat_firmware.png

       * ``BAT_AT_V1.7.1.0_1M.bin``: ESP8266モジュールに書き込むためのファームウェア。
       * ``esptool.exe``: Windows用のコマンドラインユーティリティ。
       * ``install_r3.bat``: Windowsシステム用のコマンドパッケージ。
       * ``install_r4.bat``: ``install_r3.bat`` と同じですが、UNO R4ボード専用です。

       .. raw:: html

            <br/>

    #. ターミナルを開き、先ほどダウンロードしたファームウェアフォルダに移動（ ``cd`` コマンド使用）。次に、以下のコマンドを実行して既存のファームウェアを消去し、新しいファームウェアを書き込みます。

       .. code-block::

           python3 -m esptool --chip esp8266 --before default_reset erase_flash
           python3 -m esptool --chip esp8266 --before default_reset write_flash 0 "BAT_AT_V1.7.1.0_1M.bin"

    #. 以下のプロンプトが表示された場合、ファームウェアのインストールは成功です。

       .. image:: img/install_firmware_macos.png

       .. note::
           書き込みに失敗した場合は、以下の点を確認してください。

           * ESP8266モジュールをリセットします（ESP8266アダプタのRSTをGNDに挿入し、その後抜きます）。
           * 配線が正しいか確認します。
           * コンピュータがボードを正しく認識しているか、また、ポートが使用中でないか確認します。
           * install.batファイルを再度開きます。

**3. テスト**

#. 元の配線に基づき、IO1を3V3に接続します。

   .. image:: img/connect_esp826612.png
       :width: 800

   .. raw:: html

        <br/><br/>

#. 右上隅の虫眼鏡アイコン（シリアルモニター）をクリックし、ボーレートを **115200** に設定すると、ESP8266モジュールに関する情報が表示されます。

   .. image:: img/sp20220524113020.png

   .. note::

       * ``ready`` が表示されない場合、ESP8266モジュールをリセットして（RSTをGNDに接続）、シリアルモニターを再度開きます。

#. **NEWLINE DROPDOWN BOX** をクリックし、ドロップダウンオプションで ``both NL & CR`` を選択します。 ``AT`` を入力してOKが返された場合、ESP8266はR3ボードと正常に接続されています。

   .. image:: img/sp20220524113702.png

   これで、 :ref:`config_esp8266` に従って、ESP8266モジュールの動作モードとボーレートを設定することができます。

