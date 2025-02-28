const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.resolveTargetQuery(.{ .os_tag = .linux });
    const targetWindows = b.resolveTargetQuery(.{ .os_tag = .windows });

    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "task_randomizer_linux",
        .target = target,
        .optimize = optimize,
    });

    const exeWindows = b.addExecutable(.{
        .name = "task_randomizer_windows",
        .target = targetWindows,
        .optimize = optimize,
    });

    exe.addCSourceFiles(.{ .files = &.{"src/main.c"} });
    exeWindows.addCSourceFiles(.{ .files = &.{"src/main.c"} });

    exe.linkLibC();
    exeWindows.linkLibC();

    b.installArtifact(exe);
    b.installArtifact(exeWindows);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
