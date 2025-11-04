import std.math;

const PI = 3.14;
qubit q[2];
bit c[2];

circuit my_bell_pair(q: qubit) {
    q.h();
    q.cnot(q);
}

parallel(stretch) {
    q[0].x();
    delay 10ns @ q[1];
}

c = q.measure();