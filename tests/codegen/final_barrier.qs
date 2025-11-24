qubit q[2];

parallel(stretch) {
    q[0].x();
    q[1].h();
    // Code Gen should inject barrier here
}

// This happens strictly after
q[0].z();