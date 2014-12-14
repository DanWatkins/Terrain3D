var component;
var sprite;

function createComponent(filename, parent, additionalProperties)
{
    component = Qt.createComponent(filename);
    if (component.status === Component.Ready)
        finishCreation(parent, additionalProperties);
    else
        component.statusChanged.connect(finishCreation);

    return component;
}

function finishCreation(parent, additionalProperties)
{
    if (component.status === Component.Ready) {
        sprite = component.createObject(parent, additionalProperties);

        if (sprite === null)
        {
            console.log("Error creating object");
        }
    }
    else if (component.status === Component.Error)
    {
        console.log("Error loading component:", component.errorString());
    }
}
