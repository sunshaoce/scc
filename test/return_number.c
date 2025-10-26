// RUN: gcc %s -o %s.out && ./%s.out ; echo $?
// CHECK: 21

int main() {
  return 21;
}
