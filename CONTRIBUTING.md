# Contribution Summary

If you feel like contributing, please go ahead! I'm still learning the ropes with respect to managing repositories on github, so bear with me. That being said, this is a "personal" project so I'm mostly leaving these "guidelines" for myself.

To be clear: "conventional commit" guidelines in this context refer to [this specification](https://www.conventionalcommits.org/en/v1.0.0/#specification).

In short:

- Most "work" should be done on feature branches, which are then merged into the `main` branch.
- Commit messages on feature branches _may_ follow "conventional commit" guidelines; at a minimum they _must_ be descriptive.
- Commit messages on the `main` branch _must_ follow "conventional commit" guidelines; furthermore commits to `main` _must_ be of type `fix`, `feat`, `setup` or `docs`---except for exceptional circumstances which might arise since I'm still learning the ropes of managing repositories like this.
- All commits on the `main` branch after that which is tagged 0.0.0 should also be tagged, with the tag determined via semantic versioning (i.e. `MAJOR.MINOR.PATCH`). Exceptions may be made in the case of updates which only apply to documentation.

Exceptions to the above were made in the preliminary "setup" phase of the repository-- for instance there was a short lived `dev` branch that has been abandoned in favor of merging the feature branches directly to main.

# Conventional Commit Types

The following are used as "types" for the commit messages; if I see a need to add a new type I will!

|__Type__|__Use Case__                                         |
|:------:|:----------------------------------------------------|
| fix    | fixed a bug/error                                   |
| feat   | a new feature has been added                        |
| setup  | configured settings, etc.                           |
| docs   | changes to documentation                            |
| wip    | useful on feature branches for  in-progress commits |

As always, BREAKING CHANGE is an acceptable footer, as is the BREAKING-CHANGE footer and the ! signifier in the type.

# Documentation

Please, document your code! For reference, the Doxyfile takes as input all files in the `/include/` and `/src/`, so anything which is documented with doxygen style comments will be used to generate documentation. Preferably, all classes/structs/functions/methods would be documented, even private ones! To me, it's nice to know how all of the internals work. When the engine is in a usable state, it might make more sense to supply documentation which is only based on the public facing files!
