void eonce(stack<int> &num, stack<char> &oper) {
  int x, y = num.top();
  char op = oper.top(); 
  num.pop(); oper.pop();
  if (op == '?') num.push(-y);
  else {
    x = num.top(); 
    num.pop();
    num.push(cal(x, y, op));
  }
}

int eval(char *s) {
  static int priv[256];
  stack<int> num;
  stack<char> oper;
  priv['+'] = priv['-'] = 3;
  priv['*'] = priv['/'] = 2;
  priv['('] = 10;
  int len = strlen(s);
  char last = 0;
  for (int i = 0; i < len; ++i)  {
    if (isdigit(s[i])) {
      int tmp = 0;
      while (isdigit(s[i])) {
        tmp = tmp * 10 + s[i++] - '0';
      }
      i -= 1;
      num.push(tmp);
    } else if (s[i] == '(') {
      oper.push(s[i]);
    } else if (s[i] == ')') {
      while (oper.top() != '(') {
        eonce(num, oper);
      }
      oper.pop();
    } else if (s[i] == '-' && (last == 0 || last == '(')) {
      oper.push('?'); // unary operator
    } else if (priv[s[i]] > 0) {
      while (!oper.empty() && priv[s[i]] >= priv[oper.top()]) { // >= is used for operator of left associative law
        eonce(num, oper); 
      }
      oper.push(s[i]);
    } else continue;
    last = s[i];
  }
  while (!oper.empty()) {
    eonce(num, oper);
  }
  return num.top();
}
