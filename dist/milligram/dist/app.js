document.addEventListener('DOMContentLoaded', function () {
	var btnOpen = document.getElementsByClassName("btn-menu");
	var btnClose = document.getElementsByClassName("btn-close");
	var formID = "page_form";

	var minify = function (type, text) {
		var block = document.createElement("div");
		block.className = "alert alert-" + type;
		block.innerHTML = text;

		var btn = document.createElement("button");
		btn.setAttribute("type", "button");
		btn.className = "close button button-clear";
		btn.innerHTML = '<span>&times;</span>'
		block.append(btn);
		
		document.getElementById("content").append(block);
		block.style.opacity = 1;
		btn.addEventListener("click", function(e) {
			e.preventDefault();

			e.target.closest(".alert").remove();
		});

		setTimeout(function() {
			block.remove();
		}, 3000);
	};

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

	document.getElementById("BTN_btnTest").addEventListener("click", function(e) {
		e.preventDefault();
		var els = document.getElementById(formID).elements;

        for (i = 0; i < els.length; i++) {
            els[i].disabled = true;
        }
		minify('default', 'Test!<br>Test test test <br>test');
	});
});
