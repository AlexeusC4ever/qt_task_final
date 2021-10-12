var component_ = null
var object_ = null
var objParent_ = null
var options_ = null

function createObject(url, objParent, options)
{
	objParent_ = objParent;
	options_ = options;
	component_ = Qt.createComponent(url);
	
    if(component_.status == Component.Ready)
        finishCreation();
    else
        component_.statusChanged.connect(finishCreation);
}	

function finishCreation()
{
    if(component_.status == Component.Ready)
    {
        object_ = component_.createObject(options_, objParent_);
        if(object_ == null)
            console.log("Error creating object");
    }
    else
        if(component_.status == Component.Error)
            console.log("Error creating object: ", component_.errorString());
}

function destroyObject()
{
    if (object_ != null)
    {
        object_.destroy();
        object_ = null;
    }
}
