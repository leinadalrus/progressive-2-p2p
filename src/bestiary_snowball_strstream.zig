const assert = @import("std").debug.assert;
const expect = std.testing.expect;
const mem = @import("std").mem;
const std = @import("std");

const FingerTable = struct {
    interval_matrix: [2][10]isize,
};

const FingerKeychain = struct {
    keys: [10]isize,
};

const IVirtualTable = struct {
    table_lookup_fn: fn (*IVirtualTable) FingerTable,
    nullify_sentinel_fn: fn (*IVirtualTable) FingerKeychain,

    pub fn table_lookup(interf: *IVirtualTable) FingerTable {
        return interf.table_lookup_fn(interf);
    }

    pub fn nullify_sentinel(interf: *IVirtualTable) FingerKeychain {
        return interf.nullify_sentinel_fn(interf);
    }
};

const IntervalMatrix10x10 = [2][10]isize{
    [_]isize{ 1, 0 },
    [_]isize{ 0, 1 },
    [_]isize{ 1, 0 },
    [_]isize{ 1, 1 },
    [_]isize{ 0, 495 },
};

test "finger table's interval matrix cell functionality" {
    try expect(IntervalMatrix10x10[2][10] == 495);

    for (IntervalMatrix10x10) |row, row_index| {
        for (row) |cell, column_index| {
            if (row_index == column_index) {
                try expect(cell == 495);
            }
        }
    }
}
