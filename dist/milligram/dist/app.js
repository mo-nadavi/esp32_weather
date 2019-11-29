document.addEventListener('DOMContentLoaded', function () {
    var btnOpen = document.getElementsByClassName("btn-menu");
    var btnClose = document.getElementsByClassName("btn-close");

    var eventHandlers = {
        sideOpen: function(e) {
            document.getElementById("sidebar").style.left = "0";
        },
        sideClose: function(e) {
            document.getElementById("sidebar").style.left = "-255px";
        }
    };

    btnOpen[0].addEventListener('click', eventHandlers.sideOpen);
    btnClose[0].addEventListener('click', eventHandlers.sideClose);
});
