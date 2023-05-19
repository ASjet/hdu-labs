import re
import string
from pathlib import Path
from collections import namedtuple

import pandas as pd
import matplotlib.pyplot as plt


class Analysis:
    models = ["tiny", "base", "small", "medium", "large"]
    ptn = re.compile(r"\[.*\]\s+(.*)")
    Record = namedtuple("Record", ["raw"] + models)

    def __init__(self, audio_path: str, output_path: str) -> None:
        proc = lambda s: list(
            map(
                lambda s: s.strip(string.punctuation + string.whitespace).replace(
                    "-", ""
                ),
                s.lower().split(" "),
            )
        )

        self.label: dict[str, str] = {
            audio.name.split(".")[0]: proc(
                (audio.parent / (audio.name.replace(".wav", ".txt")))
                .read_text()
                .split("\n")[0]
            )
            for audio in filter(
                lambda p: p.name.endswith(".wav"), Path(audio_path).iterdir()
            )
        }

        self.output: dict[str, str] = {
            out.name: proc(
                " ".join(
                    map(
                        lambda l: self.ptn.match(l).group(1),
                        filter(
                            lambda l: self.ptn.match(l), out.read_text().split("\n")
                        ),
                    )
                )
            )
            for out in Path(output_path).iterdir()
        }

        self.records: dict[str, self.Record] = {
            name: self.Record(
                *(
                    [text]
                    + list(map(lambda m: self.output[f"{name}-{m}.out"], self.models))
                )
            )
            for name, text in self.label.items()
        }

    def __repr__(self):
        return "\n\n".join(
            [
                "\n".join(
                    [
                        f"{field:<6}|{getattr(record, field)}"
                        for field in ["raw"] + self.models
                    ]
                )
                for record in self.records.values()
            ]
        )

    def _count(self, label: list[str], out: list[str]) -> int:
        assert len(label) == len(out)
        return len(list(filter(lambda word: word not in label, out)))

    def _score(self, label: list[str], out: list[str]) -> int:
        longer, shorter = (label, out) if len(label) > len(out) else (out, label)
        return 100 - 5 * (
            self._count(label, out)
            if len(out) == len(label)
            else min(
                [
                    self._count(longer[offset : offset + len(shorter)], shorter)
                    for offset in range(len(longer) - len(shorter))
                ]
            )
        )

    def score(self) -> pd.DataFrame:
        return pd.DataFrame(
            columns=self.records.keys(),
            data={
                name: {
                    model: self._score(record.raw, getattr(record, model))
                    for model in self.models
                }
                for name, record in self.records.items()
            },
        )

    def plot(self) -> None:
        plt.figure(figsize=(16, 8))
        scores = self.score()
        for name in self.records.keys():
            plt.plot(*tuple(zip(*scores[name].items())))
        plt.title("Different Model Size to Score")
        plt.legend(self.records.keys())
        plt.show()


if __name__ == "__main__":
    a = Analysis("audio", "output")
    print(a)
    print()
    print(
        "===================Score==================\n",
        a.score(),
        "\n==========================================",
    )
    a.plot()
