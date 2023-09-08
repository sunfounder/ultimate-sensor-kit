// Auto detect browser language and show a notification to the user to redirect to the correct language
// 右上角小窗弹出提示，提示用户切换到对应语言的页面
// 提示白色，悬浮阴影，点击跳转，点击不再提示

// Get the current language
function changeLanguage() {

    let supportLangs = {
      'en': ['This documentation is also available in', 'English', 'Never show again'],
      'de': ['Diese Dokumentation ist auch in', 'Deutsch', 'Nie wieder anzeigen'],
      'ja': ['このドキュメントは', '日本語', '今後表示しない'],
    };
  
    let pathname = window.location.pathname;
    let pageLang = ""
    if (pathname.split('/').length >= 4) {
      pageLang = pathname.split('/')[3];
    }
    let browserLang = navigator.language || navigator.userLanguage;
    browserLang = browserLang.substr(0, 2);
  
    // Check if the current language is the same as the browser language
    if (pageLang !== browserLang) {
      // Check if the current language is supported
      if (Object.keys(supportLangs).indexOf(browserLang) !== -1) {
        // Check if the current page is the default page, if so, redirect to the browser language
        if (pageLang === "") {
          newLink = window.location.protocol + '//' + window.location.host + pathname + browserLang + '/latest';
          window.location.href = newLink;
        } else {
          if (localStorage.getItem('neverShowAgain') === 'true') {
            return;
          }
          // Create link
          var link = window.location.protocol + '//' + window.location.host + pathname.replace('/' + pageLang + '/', '/' + browserLang + '/');
          // Create notification
          // 右上角小窗提示，类似右上角的消息提醒，可以选择跳转，关闭或者不在显示
          var notification = document.createElement('div');
          notification.id = 'notification';
          notification.style.cssText = `
            position: fixed;
            top: 4px;
            right: 4px;
            width: 300px;
            border-radius: 10px;
            background-color: #fff;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);
            z-index: 9999;
            padding: 12px;
            font-size: 14px;
            line-height: 1.5;
            font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
            color: #333;
          `;
          // Create text
          var text = document.createElement('p');
          text.style.cssText = 'margin: 0;';
          text.innerHTML = supportLangs[browserLang][0] + ' <a href="' + link + '">' + supportLangs[browserLang][1] + '</a>';
          // Create close button
          var closeButton = document.createElement('closeButton');
          closeButton.style.cssText = `
            position: absolute;
            top: 4px;
            right: 4px;
            width: 16px;
            height: 16px;
            background-color: transparent;
            border: 0;
            font-size: 16px;
            line-height: 1;
            color: #999;
            cursor: pointer;
          `;
          closeButton.innerHTML = '×';
          closeButton.onclick = function () {
            document.body.removeChild(notification);
          }
  
          // Create never-show button
          var neverShowButton = document.createElement('button');
          neverShowButton.style.cssText = `
            width: 100%;
            text-align: end;
            background-color: transparent;
            border: 0;
            font-size: 12px;
            line-height: 1;
            color: #999;
            cursor: pointer;
          `;
          neverShowButton.innerHTML = supportLangs[browserLang][2];
          neverShowButton.onclick = function () {
            localStorage.setItem('neverShowAgain', 'true');
            document.body.removeChild(notification);
          }
          // Append elements
          notification.appendChild(text);
          notification.appendChild(closeButton);
          notification.appendChild(neverShowButton);
          document.body.appendChild(notification);
        }
      }
    }
  }
  window.addEventListener('load', changeLanguage);