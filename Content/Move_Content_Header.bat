del /Q "..\Header\Library\Content\"

xcopy /s /d /exclude:Deny_List.txt ".\*.h" "..\Header\Library\Content\"
xcopy /s /d /exclude:Deny_List.txt ".\*.inl" "..\Header\Library\Content\"


del /Q "..\Fx\Library\Content\"

xcopy /s /d /exclude:Deny_List.txt ".\*.fx" "..\Fx\Library\Content\"