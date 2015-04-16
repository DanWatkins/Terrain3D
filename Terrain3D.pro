TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += IDE/Application
SUBDIRS += IDE/Library

IDE/Application.depends = IDE/Library
