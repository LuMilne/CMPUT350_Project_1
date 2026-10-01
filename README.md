# CMPUT 350 HW 1

## Participants:
 - Lucas Milne: (LuMilne, lemilne, 1646921)

## AI Disclosure
Detailed usage commented in "GameEngine.cpp" step 2 of Run().
When fixing project performance afte features were implemented, queried Microsoft Copilot to resolve a slowdown issue when attempting to close the window with mouse controls. Summary revealed a previously unknown issue where the program would only handle one event per frame (caused by polling with an if statement in the core loop) while mouse actions triggered multiple events. AI reccommendation to change core polling to a while statement to clear all queued events in a frame, and to add a similar while statement in the Event::Closed event fixed the issue. Discussed how this edit changed the performance of the program and confirmed mutual understanding.