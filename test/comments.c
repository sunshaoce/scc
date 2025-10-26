// RUN: gcc %s -o %s.out && ./%s.out ; echo $?
// CHECK: 23

// /*
// */
int main() {
  /* //
    return 21;
  */  //
  return /* 12 */ 23 // 56
      ;
}
