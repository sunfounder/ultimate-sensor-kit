.. _iot_add_library:

1.3 必要なライブラリの追加
---------------------------------------

BlynkをArduino IDEで使用するには、適切なライブラリを追加する必要があります。

#. |link_blynk_lib| をクリックして、 **"Assets"** までスクロールし、最初の ``.zip`` ファイルをダウンロードします。

   .. note::
    下の画像に表示されているバージョン番号は古い可能性があります。最新版をダウンロードしてインストールすることを強く推奨します。

   .. image:: img/sp220607_154840.png

#. このファイルを解凍し、 ``libraries`` フォルダに移動して次のようなフォルダを確認します。

    .. image:: img/add_lib_0.png

#. これらを全てコピーし、スケッチブックの ``libraries`` フォルダに追加します。

    **ステップ1:** ``File > Preferences > Sketchbook location`` でライブラリフォルダの場所を探す、または変更できます。

    .. image:: img/add_lib_1.png

    .. raw:: html

        <br/><br/>

    **ステップ2:** Arduino IDEからスケッチブックの場所を探し、``libraries`` フォルダをクリックして開きます。

    .. image:: img/add_lib_2.png

    .. raw:: html

        <br/><br/>

    **ステップ3:** 解凍した ``Blynk_Release_vx.x.x\libraries`` フォルダ内の全てのフォルダを、librariesフォルダに貼り付けます。

    .. image:: img/add_lib_3.png
