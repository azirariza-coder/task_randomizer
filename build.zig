const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.resolveTargetQuery(.{ .os_tag = .linux, .cpu_arch = .x86_64 });
    const targetWindows = b.resolveTargetQuery(.{ .os_tag = .windows, .cpu_arch = .x86_64 });

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

    const c_flags = [_][]const u8{
        "-Wall",
        "-Wextra",
        "-Werror",
        "-std=c99",
        "-pedantic",
    };

    exe.addCSourceFiles(.{ .files = &.{"src/main.c"}, .flags = &c_flags });
    exeWindows.addCSourceFiles(.{ .files = &.{"src/main.c"}, .flags = &c_flags });

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
