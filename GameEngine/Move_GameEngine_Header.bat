del /Q "..\Header\Library\GameEngine\"

xcopy /s /d /exclude:Deny_List.txt ".\*.h" "..\Header\Library\GameEngine\"
xcopy /s /d /exclude:Deny_List.txt ".\*.inl" "..\Header\Library\GameEngine\"


del /Q "..\Fx\Library\GameEngine\"

xcopy /s /d /exclude:Deny_List.txt ".\*.fx" "..\Fx\Library\GameEngine\"