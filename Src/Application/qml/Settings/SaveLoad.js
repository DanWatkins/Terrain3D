function cbRead(key, comboBox) {
    comboBox.currentIndex = comboBox.find(appSettings.value(key).toString());
}

function cbSave(key, comboBox) {
    appSettings.enqueueValue(key, comboBox.currentText);
}
