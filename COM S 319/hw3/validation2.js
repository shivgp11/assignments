function validation2() {
    valCheck = true;
    var email = emailCheck(document.getElementById("email").value);
    var emailRow = document.getElementById("table").rows[1].cells;
    emailRow[3].appendChild(getImage(Boolean(email), "email"));

    var phoneNumber = phoneNumberCheck(document.getElementById("phoneNumber").value);
    var phoneRow = document.getElementById("table").rows[2].cells;
    phoneRow[3].appendChild(getImage(Boolean(phoneNumber), "phoneNumber"));

    var address = addressCheck(document.getElementById("address").value);
    var addressRow = document.getElementById("table").rows[3].cells;
    addressRow[3].appendChild(getImage(Boolean(address), "address"));
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
        return false;
    }
}

function emailCheck(entry) {
    atSplit = entry.split('@');
    if (atSplit.length == 2 && alphaNumCheck(atSplit[0])) {
        periodSplit = atSplit[1].split('.')
        if (periodSplit.length == 2 && alphaNumCheck(periodSplit[0] + periodSplit[1])) {
            return true;
        }
    }
    valCheck = false;
    return false;
}
function phoneNumberCheck(entry) {
    let regex = /^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$/im;
    if (entry != null && entry.match(regex)) {
        return true;
    } else {
        return false;
    }
}
function addressCheck(entry) {
    if (entry.includes(",")) {
        atSplit = entry.split(',')
        if (atSplit.length == 2 && alphaNumCheck(atSplit[0]) && alphaNumCheck(atSplit[1])) {
            return true;
        }
        return false
    }
}