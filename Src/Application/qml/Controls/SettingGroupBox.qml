//==================================================================================================================|
// Created 2015.03.12 by Daniel L. Watkins
//
// Copyright (C) 2014-2015 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import Terrain3D 1.0

GroupBox {
    id: root

    width: parent.width

    property int settingsKey: 0
    property string title: ""
    default property alias children: body.children

    QtObject {
        id: internal
        property bool loaded: false
    }

    /**
     * Loads all children Setting components. Note that Setting components
     * automatically load themselves on creation, so this is only needed for
     * refreshing values if they changed from an outside call.
     */
    function load() {
        for (var i=0; i<body.children.length; i++)
            body.children[i].load();

        internal.loaded = true;
    }

    Column {
        id: body
        anchors.fill: parent
    }
}
