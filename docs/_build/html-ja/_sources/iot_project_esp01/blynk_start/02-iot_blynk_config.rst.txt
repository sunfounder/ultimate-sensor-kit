.. note::

    こんにちは、SunFounderのRaspberry Pi & Arduino & ESP32愛好家コミュニティへようこそ！Facebook上でRaspberry Pi、Arduino、ESP32についてもっと深く掘り下げ、他の愛好家と交流しましょう。

    **参加する理由は？**

    - **エキスパートサポート**：コミュニティやチームの助けを借りて、販売後の問題や技術的な課題を解決します。
    - **学び＆共有**：ヒントやチュートリアルを交換してスキルを向上させましょう。
    - **独占的なプレビュー**：新製品の発表や先行プレビューに早期アクセスしましょう。
    - **特別割引**：最新製品の独占割引をお楽しみください。
    - **祭りのプロモーションとギフト**：ギフトや祝日のプロモーションに参加しましょう。

    👉 私たちと一緒に探索し、創造する準備はできていますか？[|link_sf_facebook|]をクリックして今すぐ参加しましょう！

1.2 Blynkの設定
==================

#. `BLYNK <https://blynk.io/>`_ のページに移動し、 **START FREE** をクリックします。

   .. image:: img/sp220607_142551.png
        :width: 90%

   .. raw:: html

      <br/><br/>

#. ご自身のメールアドレスを入力し、アカウントを登録します。

   .. image:: img/sp220607_142807.png
        :width: 60%
        :align: center
   
   .. raw:: html

      <br/>

#. メールアドレスに届いたメールで、アカウント登録を完了させます。

   .. image:: img/sp220607_142936.png
    :width: 90%

   .. raw:: html

      <br/><br/>

#. その後、**Blynk Tour** が表示されるので、Blynkについての基本情報を把握するためにご覧ください。

   .. image:: img/sp220607_143244.png
    :width: 90%

#. 次に、この **Quick Start** でテンプレートとデバイスを作成する必要があります。**Let's go** をクリックします。

   .. image:: img/sp220607_143608.png
    :width: 90%
   
   .. raw:: html

      <br/><br/>

#. ハードウェアと接続タイプを選択します。

   .. image:: img/sp20220614173218.png
    :width: 90%

   .. raw:: html

      <br/><br/>

#. 必要なIDEが指定されますが、**Arduino IDE** を推奨します。

   .. image:: img/sp20220614173454.png
    :width: 90%
   
   .. raw:: html

      <br/><br/>

#. 必要なライブラリが表示されますが、ここで推奨されるライブラリには問題があるため、他のライブラリを手動で追加する必要があります（後述）。ここで **Next** をクリックし、新しいテンプレートとデバイスが作成されます。

   .. image:: img/sp20220614173629.png
    :width: 90%
   
   .. raw:: html

      <br/><br/>

#. 次は、関連するコードをアップロードしてBlynkにボードを接続する手順ですが、先に提供されたライブラリに問題があるため、再度他のライブラリを追加する必要があります。したがって、**Quick Start** を停止するために **Cancel** をクリックします。

   .. image:: img/sp20220614174006.png
    :width: 90%

   .. raw:: html

      <br/><br/>

#. **Search** ボタンをクリックすると、先ほど作成した新しいデバイスが表示されます。

   .. image:: img/sp20220614174410.png
    :width: 90%

   .. raw:: html

      <br/><br/>

#. この **Quickstart Device** に移動して **Device Info** をクリックすると、**Device info** ページに ``TEMPLATE_ID`` 、 ``DEVICE_NAME`` 、および ``AUTH_TOKEN`` が表示されるので、後でコピーする必要があります。

   .. image:: img/sp20220614174721.png
    :width: 90%
