file = [anyub_forwarddna.xml]

MoDeL
{
	species id = [anyub_forwarddna], name = [any unbinded forward DNA]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[species template for any forward DNA unbinded];
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
							partType:[FowardDNA];
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

