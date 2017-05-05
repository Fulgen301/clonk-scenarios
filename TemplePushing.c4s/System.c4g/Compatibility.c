/*-- Avoid errors from non-existent Engine-Functions --*/

#strict 2

global func SetGameComment() { return _inherited(...); }
