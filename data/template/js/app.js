document.addEventListener('DOMContentLoaded', function () {
    var btnOpen = document.getElementsByClassName("btn-menu");
    var btnClose = document.getElementsByClassName("btn-close");
    var sidebar = document.getElementById("sidebar");
    var content = document.getElementById("content");
    var sidebarLeft = sidebar.style.left;

    var json = "none";
    var current_page = 0;
    var obj;
    var pages;
    var cnt_menu;

    var actions = {
        load: function() {
            var hash = decodeURI(window.location.hash.substr(1));
            var xhr = new XMLHttpRequest();

            xhr.open('GET', '/echo', true);
            xhr.onload = function () {
                json = xhr.responseText;
                obj = JSON.parse(json);
                cnt_menu = obj.menu.length;
                pages = obj.content;

                if (hash) {
                    current_page = obj.menu.findIndex(function(menu) {
                        return menu == hash;
                    });
                }

                actions.menu();

                if (current_page < 0) {
                    actions.notFound();
                } else {
                    actions.content();
                }
            };
            xhr.send(null);
        },
        menu: function() {
            for (var i = 0; i < cnt_menu; i++) {
                var menu_item = document.createElement('a');

                menu_item.innerText = obj.menu[i];
                menu_item.setAttribute('href', '#' + obj.menu[i]);
                menu_item.setAttribute('data-page', i);
                
                if (current_page == i) {
                    menu_item.className = 'active';
                }

                sidebar.append(menu_item);
                menu_item.addEventListener('click', eventHandlers.pager);
            }
        },
        content: function() {
            document.getElementsByTagName("title")[0].innerText = obj.app + ': ' + obj.menu[current_page];

            var page_content = obj.content[current_page];
            var form = document.createElement("form");
            var fieldset = document.createElement("fieldset");

            for (var i = 0; i < page_content.length; i++) {
                switch (page_content[i]["html"]) {
                    case "hr":
                        var el = document.createElement("hr");
                        fieldset.append(el);
                    break;

                    case "text_block":
                        var el = document.createElement(page_content[i]["tag"]);
                        el.innerHTML = page_content[i]["text"];
                        fieldset.append(el);
                    break;

                    case "list":
                        var el = document.createElement(page_content[i]["tag"]);
                        
                        for (var ii = 0; ii < page_content[i]["list"].length; ii++) {
                            var list_item = document.createElement("li");
                            list_item.innerHTML = page_content[i]["list"][ii]["text"];
                            el.append(list_item);
                        }

                        fieldset.append(el);
                    break;

                    case "input":
                        var label = document.createElement("label");
                        label.innerHTML = page_content[i]["label"];
                        label.setAttribute("for", page_content[i]["id"]);

                        var field = document.createElement(page_content[i]["html"]);
                        field.setAttribute("type", page_content[i]["type"]);
                        field.setAttribute("id", page_content[i]["id"]);
                        field.setAttribute("value", page_content[i]["value"]);
                        
                        fieldset.append(label);
                        fieldset.append(field);
                    break;

                    case "select":
                        var label = document.createElement("label");
                        label.innerHTML = page_content[i]["label"];
                        label.setAttribute("for", page_content[i]["id"]);

                        var field = document.createElement(page_content[i]["html"]);
                        field.setAttribute("id", page_content[i]["id"]);
                        field.setAttribute("value", page_content[i]["value"]);
                        
                        for (var ii = 0; ii < page_content[i]["options"].length; ii++) {
                            var option = document.createElement("option");
                            option.innerText = page_content[i]["options"][ii]["label"];
                            option.setAttribute("value", page_content[i]["options"][ii]["value"]);
                            field.append(option);
                        }

                        fieldset.append(label);
                        fieldset.append(field);
                    break;
                }
            }

            form.append(fieldset);
            content.innerHTML = form.outerHTML;
        },
        notFound: function() {
            var not_found = document.createElement('div');

            not_found.innerHTML = '404<br>Not found';
            not_found.style.margin = 'auto';
            not_found.style.fontSize = '4.5em';
            not_found.style.textAlign = 'center';

            content.append(not_found);
        }
    };

    var utils = {
        toggleActive: function() {}
    };

    var eventHandlers = {
        sideOpen: function(e) {
            sidebar.style.left = "0";
        },
        sideClose: function(e) {
            sidebar.style.left = "-255px";
        },
        pager: function(e) {
            e.preventDefault();
            
            var el = e.target;
            var menuList = sidebar.getElementsByTagName('a');
            
            current_page = el.getAttribute('data-page');

            for (var i = 0; i < cnt_menu; i++) {
                if (current_page == i) {
                    menuList[i].classList.add('active');
                    window.location.hash = obj.menu[i];
                } else {
                    menuList[i].classList.remove('active');
                }
            }

            sidebar.style.left = sidebarLeft;
            actions.content();
        }
    };

    btnOpen[0].addEventListener('click', eventHandlers.sideOpen);
    btnClose[0].addEventListener('click', eventHandlers.sideClose);

    actions.load();
});
