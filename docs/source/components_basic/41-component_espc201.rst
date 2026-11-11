.. note::

    Hallo und willkommen in der SunFounder Raspberry Pi & Arduino & ESP32 Enthusiasten-Gemeinschaft auf Facebook! Tauchen Sie tiefer ein in die Welt von Raspberry Pi, Arduino und ESP32 mit anderen Enthusiasten.

    **Warum beitreten?**

    - **Expertenunterstützung**: Lösen Sie Nachverkaufsprobleme und technische Herausforderungen mit Hilfe unserer Gemeinschaft und unseres Teams.
    - **Lernen & Teilen**: Tauschen Sie Tipps und Anleitungen aus, um Ihre Fähigkeiten zu verbessern.
    - **Exklusive Vorschauen**: Erhalten Sie frühzeitigen Zugang zu neuen Produktankündigungen und exklusiven Einblicken.
    - **Spezialrabatte**: Genießen Sie exklusive Rabatte auf unsere neuesten Produkte.
    - **Festliche Aktionen und Gewinnspiele**: Nehmen Sie an Gewinnspielen und Feiertagsaktionen teil.

    👉 Sind Sie bereit, mit uns zu erkunden und zu erschaffen? Klicken Sie auf [|link_sf_facebook|] und treten Sie heute bei!

.. _cpn_espc201:

ESPC2-01-Modul
===============

.. image:: img/41_espc201.jpg
    :width: 400
    :align: center

Das ESPC2-01 ist ein WLAN- und Bluetooth-LE-Modul auf Basis des **ESP32-C2** (auch als
ESP8684 verkauft) von Espressif. Ein einziges Modul stellt sowohl die WLAN-Verbindung als
auch die Bluetooth-LE-Strecke für die Projekte dieses Kits bereit.

Im Modul läuft die **ESP-AT**-Firmware von Espressif, es wird also über einen seriellen
Port mit einfachen AT-Befehlen gesteuert.

Das Modul **steckt direkt im mitgelieferten WLAN-Adapter** - es sind keine Jumperkabel
nötig. Der Adapter enthält den 3,3-V-Regler und die Pegelumsetzung zwischen der 5-V-Platine
und dem 3,3-V-Modul.

Pins des ESPC2-01 und ihre Funktionen:

.. list-table:: Pins des ESPC2-01
   :widths: 20 80
   :header-rows: 1

   * - Name
     - Beschreibung
   * - 3V3
     - Spannungsversorgung, **nur 3,3 V**.
   * - GND
     - Masse.
   * - EN
     - Chip-Enable, auf dem Modul hochgezogen. Auf GND legen setzt den Chip zurück.
   * - TX0
     - UART0-Senden, GPIO20. Daten vom Modul zur Platine.
   * - RX0
     - UART0-Empfangen, GPIO19. Daten von der Platine zum Modul.
   * - IO9
     - Auswahl des Bootmodus. **Beim Einschalten** auf GND legen, um in den Downloadmodus
       zu gelangen.
   * - IO2
     - Freie IO, in diesem Kit nicht verwendet.
   * - IO3
     - Freie IO, in diesem Kit nicht verwendet.

Eigenschaften und technische Daten
-----------------------------------

* Chip: **ESP32-C2** (ESP8684H2), einkernig, 32-Bit-RISC-V
* WLAN: 802.11 b/g/n (Wi-Fi 4), **nur 2,4 GHz**
* Bluetooth: **Bluetooth LE 5.0** - klassisches Bluetooth wird nicht unterstützt
* Flash: **2 MB**
* SRAM: 272 KB
* Firmware: **ESP-AT v4.1.1.0**, eine eigene Build-Variante mit den Wi-Fi- und den
  BLE-AT-Befehlssätzen
* Serielle Schnittstelle: **115200**, 8 Datenbits, keine Parität, 1 Stoppbit, kein Flow
  Control
* UART-Pins des Moduls: TX0 = GPIO20, RX0 = GPIO19
* Versorgungsspannung: **3,3 V** (es gibt keinen 5-V-Pin)
* Spitzenstrom: **über 400 mA** beim Start von WLAN bzw. Bluetooth
* Logikpegel: **3,3 V** - die Pins sind **nicht 5-V-tolerant** (Absolutmaximum 3,6 V)
* Antenne: PCB-Antenne
* Abmessungen: **24 mm x 14 mm x 1,6 mm** (mit aufgelöteter Stiftleiste etwa 12 mm hoch)

.. important::

    Das Modul arbeitet mit **3,3 V**, seine Pins sind **nicht 5-V-tolerant**
    (Absolutmaximum 3,6 V). Der mitgelieferte Adapter erledigt die Pegelumsetzung, das
    Modul kann also direkt hineingesteckt werden - schließen Sie das Modul niemals ohne
    diesen Adapter an ein 5-V-Signal an.

    Das Kit braucht außerdem die **9-V-Batterie** (oder ein Netzteil mit 6,5 bis 12 V
    Gleichspannung). Nur über USB bricht die 3,3-V-Schiene beim Start des Moduls zusammen
    und es antwortet nie auf AT-Befehle.

* `ESP32-C2 Series - Espressif <https://www.espressif.com/en/products/socs/esp32-c2>`_
* |link_esp_at|

Weitere Projekte
-----------------

* :ref:`c201_iot_blynk_start`
