// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var $$Array                = require("bs-platform/lib/js/array.js");
var Block                  = require("bs-platform/lib/js/block.js");
var Curry                  = require("bs-platform/lib/js/curry.js");
var React                  = require("react");
var ReasonReact            = require("reason-react/src/ReasonReact.js");
var TodoItem$ReactTemplate = require("./TodoItem.bs.js");

function str(prim) {
  return prim;
}

var component = ReasonReact.reducerComponent("Page");

function updateIn(updateFn, _, valToUpdate) {
  return (function (param) {
      return $$Array.map((function (curVal) {
                    var match = +(curVal === valToUpdate);
                    if (match !== 0) {
                      return Curry._1(updateFn, curVal);
                    } else {
                      return curVal;
                    }
                  }), param);
    });
}

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (param) {
      var send = param[/* send */4];
      var match = param[/* state */2];
      return React.createElement("div", undefined, React.createElement("input", {
                      type: "text",
                      value: match[/* newTodo */0],
                      onChange: (function ($$event) {
                          var value = $$event.target.value;
                          return Curry._1(send, /* Change */Block.__(0, [value]));
                        })
                    }), React.createElement("button", {
                      onClick: (function () {
                          return Curry._1(send, /* Add */0);
                        })
                    }, "+"), React.createElement("div", undefined, $$Array.map((function (todo) {
                            return ReasonReact.element(/* None */0, /* None */0, TodoItem$ReactTemplate.make(todo, (function () {
                                              return Curry._1(send, /* Toggle */Block.__(1, [todo]));
                                            }), /* array */[]));
                          }), match[/* todos */1])));
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[
              /* newTodo */"",
              /* todos : array */[]
            ];
    });
  newrecord[/* reducer */12] = (function (action, state) {
      if (typeof action === "number") {
        return /* Update */Block.__(0, [/* record */[
                    /* newTodo */"",
                    /* todos */$$Array.append(/* array */[/* record */[
                            /* text */state[/* newTodo */0],
                            /* isChecked : false */0
                          ]], state[/* todos */1])
                  ]]);
      } else if (action.tag) {
        var todoToToggle = action[0];
        return /* Update */Block.__(0, [/* record */[
                    /* newTodo */state[/* newTodo */0],
                    /* todos */$$Array.map((function (curTodo) {
                            var match = +(curTodo === todoToToggle);
                            if (match !== 0) {
                              return /* record */[
                                      /* text */curTodo[/* text */0],
                                      /* isChecked */1 - curTodo[/* isChecked */1]
                                    ];
                            } else {
                              return curTodo;
                            }
                          }), state[/* todos */1])
                  ]]);
      } else {
        return /* Update */Block.__(0, [/* record */[
                    /* newTodo */action[0],
                    /* todos */state[/* todos */1]
                  ]]);
      }
    });
  return newrecord;
}

exports.str       = str;
exports.component = component;
exports.updateIn  = updateIn;
exports.make      = make;
/* component Not a pure module */
