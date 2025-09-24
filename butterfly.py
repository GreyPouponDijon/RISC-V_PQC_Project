import argparse
import math
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection

def generate_butterfly_segments(N: int, layers: int):
    segments_by_stage = []
    for s in range(layers):
        m = 1 << (s + 1)
        half = m >> 1
        stage_segments = []

        x0 = s
        x1 = s + 1

        for b in range(0, N, m):
            for k in range(half):
                top = b + k
                bot = b + k + half

                # Two crossing lines (X) between column s and s+1
                stage_segments.append([(x0, top), (x1, bot)])
                stage_segments.append([(x0, bot), (x1, top)])

        segments_by_stage.append(stage_segments)
    return segments_by_stage

def draw_butterfly(N=256, layers=7, point_size=2.0, linewidth=0.4, cmap_name="viridis", dark_bg=False):
    if N <= 0 or (N & (N - 1)) != 0:
        raise ValueError("N must be a positive power of two.")
    max_layers = int(math.log2(N))
    if layers < 1:
        raise ValueError("layers must be at least 1.")
    if layers > max_layers:
        raise ValueError(f"layers ({layers}) cannot exceed log2(N) = {max_layers}.")
    segments_by_stage = generate_butterfly_segments(N, layers)

    # Figure size: keep readable; scale height ~ N
    # A tall network can be compressed vertically while keeping lines visible.
    fig_w = max(8, min(18, layers * 1.2))
    fig_h = max(6, min(24, N / 16))
    fig, ax = plt.subplots(figsize=(fig_w, fig_h), constrained_layout=True)
    # Background and axes
    if dark_bg:
        fig.patch.set_facecolor("#111111")
        ax.set_facecolor("#111111")
        axis_color = "#dddddd"
    else:
        axis_color = "#222222"
    ax.set_title(f"Cooley–Tukey (radix-2) Butterfly, N={N}, layers={layers}",
             color=axis_color, fontsize=12, pad=12)
    ax.set_xlim(-0.2, layers + 0.2)
    ax.set_ylim(-0.5, N - 0.5)
    ax.invert_yaxis()  # Input 0 at the top
    ax.set_xticks(range(layers + 1))
    ax.set_xticklabels([str(s) for s in range(layers + 1)], color=axis_color)
    ax.set_yticks([])
    for spine in ax.spines.values():
        spine.set_color(axis_color)
    ax.tick_params(colors=axis_color)

    # Color map across stages for visual clarity
    cmap = plt.get_cmap(cmap_name)
    colors = [cmap(i / max(1, layers - 1)) for i in range(layers)]

    # Draw segments for each stage as a LineCollection for performance
    for s, segs in enumerate(segments_by_stage):
        lc = LineCollection(segs, colors=[colors[s]], linewidths=linewidth, alpha=0.9)
        ax.add_collection(lc)

    # Optionally draw node points at each column (0..layers)
    xs = []
    ys = []
    for x in range(layers + 1):
        xs.extend([x] * N)
        ys.extend(range(N))
    ax.scatter(xs, ys, s=point_size, c=axis_color, alpha=0.8, zorder=3)

    return fig, ax

def main():
    parser = argparse.ArgumentParser(description="Draw a Cooley–Tukey butterfly pattern.")
    parser.add_argument("--N", type=int, default=16, help="Number of inputs (power of two). Default: 256")
    parser.add_argument("--layers", type=int, default=4, help="Number of layers (stages) to draw. Default: 7")
    parser.add_argument("--save", type=str, default=None, help="Save figure to this file (e.g., butterfly.png).")
    parser.add_argument("--no-show", action="store_true", help="Do not display the plot window.")
    parser.add_argument("--dark", action="store_true", help="Use a dark background.")
    parser.add_argument("--cmap", type=str, default="viridis", help="Matplotlib colormap name. Default: viridis")
    parser.add_argument("--linewidth", type=float, default=0.4, help="Line width. Default: 0.4")
    parser.add_argument("--point-size", type=float, default=2.0, help="Node point size. Default: 2.0")
    args = parser.parse_args()

    fig, ax = draw_butterfly(N=args.N,
                         layers=args.layers,
                         point_size=args.point_size,
                         linewidth=args.linewidth,
                         cmap_name=args.cmap,
                         dark_bg=args.dark)

    if args.save:
        fig.savefig(args.save, dpi=300)
        print(f"Saved butterfly diagram to {args.save}")

    if not args.no_show:
        plt.show()

if __name__ == "__main__":
    main()
