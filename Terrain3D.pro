TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += IDE/Application
SUBDIRS += IDE/Library
SUBDIRS += IDE/gtest
SUBDIRS += IDE/Tests

IDE/Application.depends = IDE/Library
IDE/Tests.depends = IDE/Library
IDE/Tests.depends = IDE/gtest
