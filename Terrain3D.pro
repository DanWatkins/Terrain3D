TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
	IDE/Library \
	IDE/Application \
	IDE/Tests

IDE/Application.depends = IDE/Library
IDE/Tests.depends = IDE/Library
