TsfAppForResearch
===================
 
Descritpion
-------------

This application is used to research behavior of Microsoft TSF (Text Service Framework), aka TFS-aware app.
  1. Once you start the application, a timer starts automatically. What the timer does is to check whether the TSF thread manager got focus and whether there is a focused document manager. Check out codes in void CTsfAppForResearchDlg::OnTimer(UINT_PTR nIDEvent).
  1. The button, "Enable Languange Switch Watcher", allows you to watch language profile switch events sent by TSF. Click to enable the watcher and switch different IMEs to see what happens. You can switch different keyboard layouts such as English/Chinese/Japanese. And different languages such as MS Pinyin, Baidu Pinyin, Google Pinyin.

My Research Results
--------------------
  1. The ThreadManager gets focus when TextEdit control gets focus.
  1. The TextEdit control has natively TSF support. So if you put focus in the TextEdit Control, you will see the Document Manager is accessible.
  1. If you put focus to other controls like Button, the Thread manager still gets the focus but there isn't a focused document manager. So thread manager getting focus doesn't mean, there is a focused document manager.

Related Codes
--------------------
   1. TsfManager.cpp: LW class to encapsulate some TSF APIs.
   2. TsfAppForResearchDlg.cpp: Invoke TSFManager APIs.
