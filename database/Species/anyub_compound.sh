file = [anyub_compound.xml]

MoDeL
{
	species id = [anyub_compound], name = [any unbinded compound]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[species template for any compound unbinded];
		}
		cnModel
		{
			listOfChains
			{
				chain
				{
					listOfParts
					{
						part
						{
							partReference:[ANYUB];
							partLabel:[ANYUB];
							partType:[Compound];
							partCategory:[substituent];
						}
					}
				}
			}
			listOfTrees
			{
			}
		}
		listOfReferencedReactions
		{
			referencedReaction:[tm_degradation] speciesType = [reactant];
		}
	}
}

