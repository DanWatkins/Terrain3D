//checked
function checkedRead(key, checkBox) {
    checkBox.checked = appSettings.value(key);
}

function checkedSave(key, checkBox) {
    appSettings.enqueueValue(key, checkBox.checked);
}



//value
function valueRead(key, spinBox) {
    spinBox.value = appSettings.value(key);
}

function valueSave(key, spinBox) {
    appSettings.enqueueValue(key, spinBox.value);
}


//ComboBox
function cbRead(key, comboBox) {
    comboBox.currentIndex = comboBox.find(appSettings.value(key).toString());
}

function cbSave(key, comboBox) {
    appSettings.enqueueValue(key, comboBox.currentText);
}
