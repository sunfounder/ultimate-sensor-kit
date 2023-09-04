# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------
import sphinx_rtd_theme
import time

project = 'SunFounder Ultimate Sensor Kit'
copyright = f'{time.localtime().tm_year}, SunFounder'
author = 'www.sunfounder.com'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = ['sphinx.ext.autosectionlabel'
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_static_path = ['_static']
html_theme = 'sphinx_rtd_theme'
html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]


# SunFounder logo

html_js_files = [
    'https://ezblock.cc/readDocFile/custom.js',
]
html_css_files = [
    'https://ezblock.cc/readDocFile/custom.css',
]

#### RTD+

# html_js_files = [
#     'https://ezblock.cc/readDocFile/custom.js',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/js/ace.js',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/js/ext-language_tools.js',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/js/theme-chrome.js',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/js/mode-python.js',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/js/mode-sh.js',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/js/monokai.js',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/js/xterm.js',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/js/FitAddon.js',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/js/readTheDocIndex.js',

# ]
# html_css_files = [
#     'https://ezblock.cc/readDocFile/custom.css',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/css/index.css',
#     'https://ezblock.cc/readDocFile/readTheDoc/src/css/xterm.css',
# ]



# Multi-language

language = 'en' # Before running make html, set the language.
locale_dirs = ['locale/'] # .po files for other languages are placed in the locale/ folder.

gettext_compact = False # Support for generating the contents of the folders inside source/ into other languages.



# open link in a new window

rst_epilog = """


.. |link_download_arduino| raw:: html

    <a href="https://www.arduino.cc/en/software" target="_blank">Arduino IDE 2.0.0 Page</a>

.. |link_install_arduino_linux| raw:: html

    <a href="https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing#linux" target="_blank"> Installing the Arduino IDE 2 - Linux </a>
    
.. |link_ascii| raw:: html

    <a href="https://www.asciitable.com/" target="_blank">ASCII table of characters</a>

.. |link_esp8266_at| raw:: html

    <a href="/_static/pdf/esp8266_at_instruction_set_en.pdf" target="_blank">ESP8266 AT Instruction Set</a>

.. |link_blynk_lib| raw:: html

    <a href="https://github.com/blynkkk/blynk-library/releases" target="_blank">HERE</a>

.. |link_r4_datasheet| raw:: html

    <a href="https://docs.arduino.cc/resources/datasheets/ABX00080-datasheet.pdf" target="_blank">Arduino UNO R4 Minima Datasheet</a> 

.. |link_ra4m1_datasheet| raw:: html

    <a href="https://docs.arduino.cc/resources/datasheets/ra4m1-datasheet.pdf" target="_blank">Renesas RA4M1 Group Datasheet</a> 


.. |link_uno_r4| raw:: html

    <a href="https://docs.arduino.cc/hardware/uno-r4-minima" target="_blank">Arduino UNO R4 Minima</a> 

.. |link_blynk_logEvent| raw:: html

    <a href="https://docs.blynk.io/en/getting-started/events-tutorial#use-blynk.logevent-firmware-api" target="_blank">Blynk.logEvent()</a> 

.. |link_blynk_virtualWrite| raw:: html

    <a href="https://docs.blynk.io/en/blynk-library-firmware-api/virtual-pins#blynk.virtualwrite-vpin-value" target="_blank">Blynk.virtualWrite()</a> 

.. |link_blynk_timer_intro| raw:: html

    <a href="https://docs.blynk.io/en/legacy-platform/legacy-articles/keep-your-void-loop-clean" target="_blank">Why we use Blynk timer?</a> 

.. |link_blynk_quickstart| raw:: html

    <a href="https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/quickstart-device-code-overview" target="_blank">Blynk Quickstart</a> 

.. |link_blynk_doc| raw:: html

    <a href="https://docs.blynk.io/" target="_blank">Blynk Documentation</a> 

.. |link_blynk_syncing| raw:: html

    <a href="https://docs.blynk.io/en/blynk-library-firmware-api/state-syncing#for-hardware" target="_blank">Blynk - State Syncing</a> 

.. |link_blynk_write| raw:: html

    <a href="https://docs.blynk.io/en/getting-started/using-virtual-pins-to-control-physical-devices#the-blynk_write-vpin-function" target="_blank">Blynk - BLYNK_WRITE()</a>    

.. |link_blynk_LED_color| raw:: html

    <a href="https://docs.blynk.io/en/blynk.apps/widgets-displays/led#set-widget-color" target="_blank">Blynk - LED</a>  

.. |link_blynk_displays| raw:: html

    <a href="https://docs.blynk.io/en/blynk.apps/widgets-displays" target="_blank">Blynk - Widgets Displays</a>  

.. |link_blynk_timer| raw:: html

    <a href="https://docs.blynk.io/en/blynk-library-firmware-api/blynk-timer" target="_blank">Blynk - Timers</a>  

.. |link_ifttt| raw:: html

    <a href="https://ifttt.com/" target="_blank">IFTTT</a>  

.. |link_ifttt_welcome| raw:: html

    <a href="https://ifttt.com/explore/welcome_to_ifttt" target="_blank">IFTTT - Welcome to IFTTT</a> 

.. |link_ifttt_webhook_faq| raw:: html

    <a href="https://help.ifttt.com/hc/en-us/articles/115010230347-Webhooks-service-FAQ" target="_blank">IFTTT - Webhooks service FAQ</a> 

.. |link_thingspeak| raw:: html

    <a href="https://thingspeak.com/" target="_blank">ThingSpeak</a> 

.. |link_appinventor| raw:: html

    <a href="http://appinventor.mit.edu/" target="_blank">MIT App Inventor</a>

.. |link_appinventor_login| raw:: html

    <a href="http://appinventor.mit.edu/explore/get-started" target="_blank">Get Started with MIT App Inventor</a>

.. |link_heat_index| raw:: html

    <a href="https://en.wikipedia.org/wiki/Heat_index" target="_blank">heat index</a>

.. |link_PCF8574_Datasheet| raw:: html

    <a href="https://www.ti.com/lit/ds/symlink/pcf8574.pdf?ts=1627006546204" target="_blank">PCF8574 Datasheet</a>

.. |link_image2cpp| raw:: html

    <a href="http://javl.github.io/image2cpp/" target="_blank">image2cpp</a>

.. |link_arduino-songs| raw:: html

    <a href="https://github.com/robsoncouto/arduino-songs" target="_blank">robsoncouto/arduino-songs</a>    

.. |link_speech_recognition| raw:: html

    <a href="https://play.google.com/store/apps/details?id=com.google.android.tts" target="_blank">Speech Recognition & Synthesis</a>  

.. |link_language_tag| raw:: html

    <a href="https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes" target="_blank">List of ISO 639-1 codes</a>  

.. |link_serial_bluetooth_terminal| raw:: html

    <a href="https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal" target="_blank">Serial Bluetooth Terminal</a>  

.. |link_blynk| raw:: html

    <a href="https://blynk.io/" target="_blank">Blynk</a> 


    
"""