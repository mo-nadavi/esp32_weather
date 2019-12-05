document.addEventListener('DOMContentLoaded', function () {
	var btnOpen = document.getElementsByClassName("btn-menu");
	var btnClose = document.getElementsByClassName("btn-close");
	var formID = "page_form";

	var minify = function (type, text) {
		var Timer = function(callback, delay) {
		    var timerId, start, remaining = delay;

		    this.pause = function() {
		        window.clearTimeout(timerId);
		        remaining -= Date.now() - start;
		        console.log(111);
		    };

		    this.resume = function() {
		        start = Date.now();
		        window.clearTimeout(timerId);
		        timerId = window.setTimeout(callback, remaining);
		    };

		    this.resume();
		};

		var timer = new Timer(function () {
			block.remove();
		}, 1000, block);

		var block = document.createElement("div");
		block.className = "alert alert-" + type;
		block.innerHTML = text;

		var btn = document.createElement("button");
		btn.setAttribute("type", "button");
		btn.className = "close button button-clear";
		btn.innerHTML = '<span>&times;</span>'
		block.append(btn);
		
		document.getElementById("content").appendChild(block);
		btn.addEventListener("click", function(e) {
			e.preventDefault();

			e.target.closest(".alert").remove();
		});

		block.addEventListener("mouseover", function() {
			timer.pause();
		});

		block.addEventListener("mouseout", function() {
			timer.resume();
		});

		// setTimeout(function() {
		// 	block.remove();
		// }, 1000);
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
		// var els = document.getElementById(formID).elements;

  //       for (i = 0; i < els.length; i++) {
  //           els[i].disabled = true;
  //       }
		minify('success', 'OK!');
	});
});
