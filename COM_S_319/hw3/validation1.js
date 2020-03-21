function validation1() {
    valCheck = true;
    var firstName = alphaNumCheck(document.getElementById("firstName").value);
    var firstNameRow = document.getElementById("table").rows[1].cells;
    firstNameRow[3].appendChild(getImage(Boolean(firstName), "firstName"));

    var lastName = alphaNumCheck(document.getElementById("lastName").value);
    var lastNameRow = document.getElementById("table").rows[2].cells;
    lastNameRow[3].appendChild(getImage(Boolean(lastName), "lastName"));

    var gender = selectionCheck(document.getElementById("gender").value);
    var genderRow = document.getElementById("table").rows[3].cells;
    genderRow[3].appendChild(getImage(Boolean(gender), "gender"));

    var state = selectionCheck(document.getElementById("state").value);
    var stateRow = document.getElementById("table").rows[4].cells;
    stateRow[3].appendChild(getImage(Boolean(state), "state"));
	
	if(valCheck) {
		window.location ="validation2.html";
	}
}

function getImage(bool, ID) {
    var image = document.getElementById("image" + ID);
    if (image == null) {
        image = new Image(15, 15);
        image.id = "image" + ID;
    }
    image.src = bool ? './correct.png' : './wrong.png';
    return image;
}

function alphaNumCheck(entry) {
    let regex = /^[a-z0-9]+$/i;
    if (entry != null && entry.match(regex)) {
        return true;
    } else {
		valCheck = false;
        return false;
		
    }
}

// Check gender and state selection
function selectionCheck(option)
{
    if (option == "cali" || option == "florida" || option == "newYork" || option == "texas" || option == "hawaii"
        || option == "washington" || option == "colorado" || option == "virginia" || option == "iowa" || option == "arizona"
        || option == "male" || option == "female")
    {
        return true;
    } else {
        return false;
    }

}
