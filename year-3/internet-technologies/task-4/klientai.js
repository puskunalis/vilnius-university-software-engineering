function validateID() {
    var maxID = 999999999

    if (!Number.isInteger(+$("#id").val()) || $("#id").val() <= 0) {
        $("#id").attr("style", "box-shadow: 0 0 3px #FF0000;")
        $("#id-validation-error").removeAttr("style")
        $("#id-validation-error").text("ID privalo būti teigiamas sveikasis skaičius.")
        return false
    } else if ($("#id").val() > maxID) {
        $("#id").attr("style", "box-shadow: 0 0 3px #FF0000;")
        $("#id-validation-error").removeAttr("style")
        $("#id-validation-error").text("ID reikšmė per didelė, didžiausia galima reikšmė: " + maxID)
        return false
    } else {
        $("#id").removeAttr("style")
        $("#id-validation-error").attr("style", "display: none;")
        return true
    }
}

function validateName() {
    if ($("#vardas").val().length <= 0) {
        $("#vardas").attr("style", "box-shadow: 0 0 3px #FF0000;")
        $("#vardas-validation-error").removeAttr("style")
        return false
    } else {
        $("#vardas").removeAttr("style")
        $("#vardas-validation-error").attr("style", "display: none;")
        return true
    }
}

function validateSurname() {
    if ($("#pavarde").val().length <= 0) {
        $("#pavarde").attr("style", "box-shadow: 0 0 3px #FF0000;")
        if ($("form").find("#pavarde-validation-error").length == 0) {
            $("#pavarde").after('<p id="pavarde-validation-error">Pavardės laukas negali būti tuščias.</p>')
        }
        return false
    } else {
        $("#pavarde").removeAttr("style")
        $("#pavarde-validation-error").remove()
        return true
    }
}

function validateDate() {
    const regexpDate = /^(\d{4})-(\d{2})-(\d{2})$/

    var match = $("#gimimo-data").val().match(regexpDate)

    if (match === null) {
        $("#gimimo-data").attr("style", "box-shadow: 0 0 3px #FF0000;")
        $("#gimimo-data-validation-error").removeAttr("style")
        return false
    } else {
        var year = parseInt(match[1])
        var month = parseInt(match[2]) - 1
        var day = parseInt(match[3])

        var date = new Date(year, month, day)

        if (date.getDate() !== day) {
            $("#gimimo-data").attr("style", "box-shadow: 0 0 3px #FF0000;")
            $("#gimimo-data-validation-error").removeAttr("style")
            return false
        } else {
            $("#gimimo-data").removeAttr("style")
            $("#gimimo-data-validation-error").attr("style", "display: none;")
            return true
        }
    }
}

function validateForm() {
    return [validateID, validateName, validateSurname, validateDate].filter(x => !x()).length === 0
}

$(document).ready(function() {
    $.getJSON("https://jsonblob.com/api/jsonBlob/1027626193511530496", function(data) {
        $.each(data.klientai, function(index, element) {
            $("<tr>").append(
                $("<td>").text(element.id),
                $("<td>").text(element.vardas),
                $("<td>").text(element.pavarde),
                $("<td>").text(element.gimimoData),
                $("<td>").text(element.saskaituTipas),
                $("<td>").text(element.paskyrosTipas),
            ).appendTo("#klientu-informacija")
        })
    })

    $("#id").change(validateID)

    $("#vardas").change(validateName)

    $("#pavarde").change(validateSurname)

    $("#gimimo-data").change(validateDate)

    $("input[name='saskaituTipas']").change(function() {
        if ($("form").find("#paskyros-tipas").length === 0) {
            $("input[name='saskaituTipas']").parent().after(`
            <p>
                <label for="paskyros-tipas">Vartotojo paskyros tipas</label><br>
                <select name="paskyros-tipas" id="paskyros-tipas">
                    <option value="iprastas">Įprastas</option>
                    <option value="jaunimo">Jaunimo</option>
                    <option value="verslo">Verslo</option>
                </select>
            </p>
            `)
        }
    })

    $("form").submit(function(event) {
        event.preventDefault()

        if (!validateForm()) {
            return
        }

        var element = {
            id: $("#id").val(),
            vardas: $("#vardas").val(),
            pavarde: $("#pavarde").val(),
            gimimoData: $("#gimimo-data").val(),
            saskaituTipas: $("input[name='saskaituTipas']:checked").val(),
            paskyrosTipas: $("#paskyros-tipas").val(),
        }

        $.getJSON("https://jsonblob.com/api/jsonBlob/1027626193511530496", function(data) {
            $.ajax({
                url: "https://jsonblob.com/api/jsonBlob/1027626193511530496",
                type: "PUT",
                contentType: "application/json",
                data: function() {
                    data.klientai.push(element)
                    return JSON.stringify(data)
                }(),
                success: function(response) {
                    $("<tr>").append(
                        $("<td>").text(element.id),
                        $("<td>").text(element.vardas),
                        $("<td>").text(element.pavarde),
                        $("<td>").text(element.gimimoData),
                        $("<td>").text(element.saskaituTipas),
                        $("<td>").text(element.paskyrosTipas),
                    ).appendTo("#klientu-informacija")
                }
            })
        })
    })
})
